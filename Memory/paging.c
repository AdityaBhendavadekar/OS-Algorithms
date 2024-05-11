#include <stdio.h>

int  PAGE_SIZE = 4096;

int translateAddress(int logical_address, int *page_table) {
    int page_number = logical_address / PAGE_SIZE;
    int offset = logical_address % PAGE_SIZE;
    int frame_number = page_table[page_number];
    int physical_address = (frame_number * PAGE_SIZE) + offset;
    return physical_address;
}

int main() {
    int page_table[4] = {2, 4, 1, 3}; 

    int logical_address;
    printf("Enter the logical address: ");
    scanf("%d", &logical_address);

    int physical_address = translateAddress(logical_address, page_table);

    printf("Logical Address: %d\n", logical_address);
    printf("Physical Address: %d\n", physical_address);

    return 0;
}
