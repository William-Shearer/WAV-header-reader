// Modifies the volume of an audio file

// This is a modification of the source file on CS50.
// Its only purpose is to read and translate the header
// file to human readable form.
// The best guide is at: http://soundfile.sapp.org/doc/WaveFormat/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./volume input.wav\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    uint8_t header_file[HEADER_SIZE];

    fread(header_file, sizeof(uint8_t), HEADER_SIZE, input);

    printf("Chunk ID:\t\t");
    for (int i = 0; i < 4; i++)
    {
        printf("%c", header_file[i]);
    }
    printf("\n");

    uint32_t chunk_size = 0;
    uint8_t *gen_bytes = (uint8_t *)&chunk_size;
    // Little endian
    gen_bytes[0] = header_file[4];
    gen_bytes[1] = header_file[5];
    gen_bytes[2] = header_file[6];
    gen_bytes[3] = header_file[7];
    printf("Chunk Size (bytes):\t%u\n", chunk_size);

    printf("Format:\t\t\t");
    for (int i = 8; i < 12; i++)
    {
        printf("%c", header_file[i]);
    }
    printf("\n");

    printf("SubChunk1 ID:\t\t");
    for (int i = 12; i < 16; i++)
    {
        printf("%c", header_file[i]);
    }
    printf("\n");

    uint32_t sub_chunk_size = 0;
    gen_bytes = (uint8_t *)&sub_chunk_size;
    gen_bytes[0] = header_file[16];
    gen_bytes[1] = header_file[17];
    gen_bytes[2] = header_file[18];
    gen_bytes[3] = header_file[19];
    printf("SubChunk Size (bytes):\t%u\n", sub_chunk_size);

    uint16_t audio_format = 0;
    gen_bytes = (uint8_t *)&audio_format;
    gen_bytes[0] = header_file[20];
    gen_bytes[1] = header_file[21];
    printf("Audio format:\t\t%u\n", audio_format);

    uint16_t num_channels = 0;
    gen_bytes = (uint8_t *)&num_channels;
    gen_bytes[0] = header_file[22];
    gen_bytes[1] = header_file[23];
    printf("Num Channels:\t\t%u\n", num_channels);

    uint32_t sample_rate = 0;
    gen_bytes = (uint8_t *)&sample_rate;
    gen_bytes[0] = header_file[24];
    gen_bytes[1] = header_file[25];
    gen_bytes[2] = header_file[26];
    gen_bytes[3] = header_file[27];
    printf("Sample Rate:\t\t%u\n", sample_rate);

    uint32_t byte_rate = 0;
    gen_bytes = (uint8_t *)&byte_rate;
    gen_bytes[0] = header_file[28];
    gen_bytes[1] = header_file[29];
    gen_bytes[2] = header_file[30];
    gen_bytes[3] = header_file[31];
    printf("Byte Rate:\t\t%u\n", byte_rate);

    uint16_t block_align = 0;
    gen_bytes = (uint8_t *)&block_align;
    gen_bytes[0] = header_file[32];
    gen_bytes[1] = header_file[33];
    printf("Block Align:\t\t%u\n", block_align);

    uint16_t bits_per_sample = 0;
    gen_bytes = (uint8_t *)&bits_per_sample;
    gen_bytes[0] = header_file[34];
    gen_bytes[1] = header_file[35];
    printf("Bits per Sample:\t%u\n", bits_per_sample);

    printf("SubChunk2 ID:\t\t");
    for (int i = 36; i < 40; i++)
    {
        printf("%c", header_file[i]);
    }
    printf("\n");

    uint32_t sub_chunk2_size = 0;
    gen_bytes = (uint8_t *)&sub_chunk2_size;
    gen_bytes[0] = header_file[40];
    gen_bytes[1] = header_file[41];
    gen_bytes[2] = header_file[42];
    gen_bytes[3] = header_file[43];
    printf("Sub Chunk2 Size (data):\t%u\n", sub_chunk2_size);

    fclose(input);
}
