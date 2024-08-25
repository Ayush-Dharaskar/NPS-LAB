#include <stdio.h>
#include <stdlib.h>

#define BUCKET_SIZE 10
#define OUTGOING_RATE 1

// Structure to represent the leaky bucket
struct LeakyBucket {
    int size; // Current size of the bucket
};

// Initialize the leaky bucket
void initLeakyBucket(struct LeakyBucket *bucket) {
    bucket->size = 0;
}

// Add packet to the leaky bucket
void addPacket(struct LeakyBucket *bucket, int packetSize, int time) {
    printf("Packet arrived at time %d, size = %d bytes\n", time, packetSize);
    
    if (bucket->size + packetSize <= BUCKET_SIZE) {
        bucket->size += packetSize;
        printf("Packet conforms. Added to the bucket. Current bucket size = %d bytes\n", bucket->size);
    } else {
        printf("Packet does not conform. Dropped.\n");
    }
}

// Remove packets from the leaky bucket based on outgoing rate
void removePackets(struct LeakyBucket *bucket, int time) {
    //printf("Time: %d. Outgoing rate: %d byte/second\n", time, OUTGOING_RATE);
    while (bucket->size > 0) {
        //printf("Bucket size before removal: %d bytes\n", bucket->size);
        bucket->size -= OUTGOING_RATE;
        if (bucket->size < 0)
            bucket->size = 0;
        //printf("Packet sent. Current bucket size = %d bytes\n", bucket->size);
    }
}

int main() {
    // Initialize the leaky bucket
    struct LeakyBucket bucket;
    initLeakyBucket(&bucket);

    // Arrival times of network packets
    int arrivalTimes[] = {1, 2, 3, 5, 6, 8, 11, 12, 15, 16, 19};
    int numPackets = sizeof(arrivalTimes) / sizeof(arrivalTimes[0]);

    // Process each packet
    for (int i = 0; i < numPackets; i++) {
        int packetSize = 4; // Packet size is 4 bytes
        addPacket(&bucket, packetSize, arrivalTimes[i]);
        removePackets(&bucket, arrivalTimes[i]);
    }

    return 0;
}
