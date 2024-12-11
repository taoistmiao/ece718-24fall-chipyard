#include "rocc.h"

static inline void spmm_write(int idx, unsigned long data)
{
	ROCC_INSTRUCTION_SS(0, data, idx, 0);
}

static inline unsigned long spmm_read(int idx)
{
	unsigned long value;
	ROCC_INSTRUCTION_DSS(0, value, 0, idx, 1);
	return value;
}

static inline void spmm_load(int idx, void *ptr)
{
	asm volatile ("fence");
	ROCC_INSTRUCTION_SS(0, (uintptr_t) ptr, idx, 2);
}

static inline void spmm_store(int idx, void *ptr)
{
	ROCC_INSTRUCTION_SS(0, (uintptr_t) ptr, idx, 3);
    asm volatile ("fence");
}

static inline void spmm_add(int idx, unsigned long addend)
{
	ROCC_INSTRUCTION_SS(0, addend, idx, 4);
}

static inline void spmm_mac(int idx)
{
	ROCC_INSTRUCTION_SS(0, 0, idx, 5);
}

typedef struct
{
    int data;
    int col;
} element;

int main(void) {
    uint8_t vec[5] = {0,1,2,3,4};
    uint8_t vec_2x[5] = {0};
    spmm_load(1, &vec);
    spmm_write(2, 2);
    spmm_mac(0);
    spmm_store(0, &vec_2x);
    for (int i = 0; i < 5; i++) {
        if (vec[i] != vec_2x[i]-vec[i]) {
            return i+1;
        }
    }
    return 0;
}

// int main(void)
// {
// 	element C0[5] = {0};

//     element A0[3] = {
//         {1,0},{2,2},{3,4}
//     };

//     element B0[2] = {
//         {3,0},{3,3}
//     };

//     element B2[1] = {
//         {4,2}
//     };

//     element B4[1] = {
//         {4,4}
//     };


// 	spmm_load(0, &A0);
//     spmm_load(1, &B0);
//     spmm_load(2, &B2);
//     spmm_load(3, &B4);
// 	spmm_mac(4);
// 	spmm_store(4, &C0);

// 	if (C0[0].data != 3 || C0[2].data != 8 || C0[3].data != 3 || C0[4].data != 12) {
//         return 1;
//     }

// 	return 0;
// }
