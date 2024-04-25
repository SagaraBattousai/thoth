#include <string.h>

#include <thoth/crypto/keccak.h>

static void keccak(uint32_t rate, uint32_t capacity, const uint8_t *input,
	int byteCount, uint8_t delimitedSuffix, uint8_t *output, int outputByteCount);


void keccak224(const uint8_t *input, int byteCount, uint8_t *output)
{
	keccak(1152, 448, input, byteCount, 0x06, output, 28);
}

void keccak256(const uint8_t *input, int byteCount, uint8_t *output)
{
	keccak(1088, 512, input, byteCount, 0x06, output, 32);
}

void keccak384(const uint8_t *input, int byteCount, uint8_t *output)
{
	keccak(832, 768, input, byteCount, 0x06, output, 48);
}

void keccak512(const uint8_t *input, int byteCount, uint8_t *output)
{
	keccak(576, 1024, input, byteCount, 0x06, output, 64);
}

/*
==========================
Actual Code
==========================
*/


static const int endianTest = 0xABCDEF37;
static const char littleEndianValue = 0x37;
//static const int bigEndianValue = 0xAB;


#define system_is_little_endian \
	((*(const char*)&endianTest) == littleEndianValue)

#define system_is_big_endian \
	((*(const char*)&endianTest) == bigEndianValue)

typedef uint64_t keccak_lane_t;

//To avoid casting, just don't use lane as anything other than keccak_lane_t
#define rotateLane(lane, offset) ( (lane << offset) | (lane >> (-offset & 63)) )
#define laneIndex(x, y) ((x) + 5 * (y))

static keccak_lane_t readLane(const uint8_t *state, int x, int y)
{
	if (system_is_little_endian)
	{
		return ((keccak_lane_t*)state)[laneIndex(x, y)];
	}

	//otherwise:
	int offset = sizeof(keccak_lane_t) * laneIndex(x, y);
	keccak_lane_t lane = (state + offset)[7];

	for (int i = 6; i >= 0; --i)
	{
		lane <<= 8;
		lane |= (state + offset)[i];
	}

	return lane;
}

static void writeLane(uint8_t *state, int x, int y, keccak_lane_t lane)
{
	if (system_is_little_endian)
	{
		((keccak_lane_t*)state)[laneIndex(x, y)] = lane;
	}
	else
	{
		int offset = sizeof(keccak_lane_t) * laneIndex(x, y);

		for (int i = 0; i < 8; ++i)
		{
			(state + offset)[i] = (uint8_t) lane; //feel like I want to use &(0x..) to be safer
			lane >>= 8;
		}
	}
}

static void XORLane(uint8_t *state, int x, int y, keccak_lane_t lane)
{
	if (system_is_little_endian)
	{
		((keccak_lane_t*)state)[laneIndex(x, y)] ^= lane;
	}
	else
	{
		int offset = sizeof(keccak_lane_t) * laneIndex(x, y);
		//keccak_lane_t lane = (state + offset)[7];

		for (int i = 0; i < 8; ++i)
		{
			(state + offset)[i] ^= lane; //feel like I want to use &(0x..) to be safer
			lane >>= 8;
		}
	}
}

//I don't understand this function!!!!
//And I really don't understand the next one that depends upon this one!
static int LFSR86540(uint8_t *LFSR)
{
	int result = (*LFSR & 0x01) != 0;
	if ((*LFSR & 0x80) != 0)
	{
		*LFSR = (*LFSR << 1) ^ 0x71;
	}
	else 
	{
		*LFSR <<= 1;
	}

	return result;
}

//I Really don't understand this function!
static void keccak_f1600_state_permute(uint8_t *state)
{
	uint8_t LFSR_state = 0x01;

	for (int round = 0; round < 24; ++round)
	{
		keccak_lane_t C[5];
		keccak_lane_t D;

		//Column parity
		for (int x = 0; x < 5; ++x)
		{
			C[x] = readLane(state, x, 0) ^
				readLane(state, x, 1) ^
				readLane(state, x, 2) ^
				readLane(state, x, 3) ^
				readLane(state, x, 4);
		}

		for (int x = 0; x < 5; ++x)
		{
			//Compute theta
			D = C[(x + 4) % 5] ^ rotateLane(C[(x + 1) % 5], 1);
			//add theta to whole column
			for (int y = 0; y < 5; ++y)
			{
				XORLane(state, x, y, D);
			}
		}

		//keccak team used scope {} here

		int x = 1;
		int y = 0;

		keccak_lane_t current = readLane(state, x, y);
		keccak_lane_t temp;

		for (int t = 0; t < 24; ++t)
		{
			int r = ((t + 1) * (t + 2) / 2) % 64;
			int Y = (2 * x + 3 * y) % 5;
			x = y;
			y = Y;
			temp = readLane(state, x, y);
			writeLane(state, x, y, rotateLane(current, r));
			current = temp;
		}

		keccak_lane_t temp_plane[5];
		for (y = 0; y < 5; ++y)
		{
			for (x = 0; x < 5; ++x)
			{
				temp_plane[x] = readLane(state, x, y);
			}

			for (x = 0; x < 5; ++x)
			{
				writeLane(state, x, y, temp_plane[x] ^
					((~temp_plane[(x + 1) % 5]) & temp_plane[(x + 2) % 5]));
			}
		}

		for (int j = 0; j < 7; ++j)
		{
			unsigned int bitPosition = (1 << j) - 1; // 2^j - 1
			if (LFSR86540(&LFSR_state))
			{
				XORLane(state, 0, 0, (keccak_lane_t)1 << bitPosition);
			}
		}
	}
}


#define MIN(a, b) ((a) < (b) ? (a) : (b))

static void keccak(uint32_t rate, uint32_t capacity, const uint8_t *input,
	int byteCount, uint8_t delimitedSuffix, uint8_t *output, int outputByteCount)
{
	uint8_t state[200]; //200 bytes as state is a 1600 bit cube
	uint32_t rate_bytes = rate >> 3; //rate / 8
	uint32_t block_size = 0;

	if ((rate + capacity) != 1600 || (rate % 8) != 0)
		return;

	memset(state, 0, sizeof(state));

	// Absorb input blocks
	while (byteCount > 0)
	{
		block_size = MIN((uint32_t) byteCount, rate_bytes);
		for (uint32_t i = 0; i < block_size; i++)
		{
			state[i] ^= input[i];
		}
		input += block_size;
		byteCount -= block_size;

		if (block_size == rate_bytes)
		{
			keccak_f1600_state_permute(state);
			block_size = 0;
		}
	}

	//Padding and squeezing time
	state[block_size] ^= delimitedSuffix;

	if (((delimitedSuffix & 0x80) != 0) && (block_size == (rate_bytes - 1)))
	{
		keccak_f1600_state_permute(state);
	}

	//AKA Read from end. We know this is right even though compiler can't
	state[rate_bytes - 1] ^= 0x80;

	keccak_f1600_state_permute(state);

	while (outputByteCount > 0)
	{
		block_size = MIN((uint32_t) outputByteCount, rate_bytes);
		memcpy(output, state, block_size);
		output += block_size;
		outputByteCount -= block_size;

		if (outputByteCount > 0)
		{
			keccak_f1600_state_permute(state);
		}
	}

}
