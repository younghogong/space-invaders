#include "soundConverter.h"

void usage();
bool fileExists(const char* filename);
void writeHeader(FILE *file);
// ----------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    // fd's for our files
    FILE *input;
    FILE *output;

    // check for the proper number of arguments
    if (argc != 3) {
        usage();
        return -EINVAL;
    }

    // store the name of the sound
    char *soundName = argv[2];

    // open the inputWAV file passed to us for reading binary ('rb')
    input = fopen(argv[1], "rb");

    // make sure file even exists
    if (!input) {
        printf("Error opening %s\n", argv[1]);
        return -ENOENT;
    }

    // set up our destination location
    if (!fileExists(OUTPUT_FILE)) {
        printf("Creating %s...\n", OUTPUT_FILE);

        // open for appending
        output = fopen(OUTPUT_FILE, "a+");
        writeHeader(output);
    } else {
        // else, just open. Don't write header
        output = fopen(OUTPUT_FILE, "a+");
    }

    // create some space and a comment
    fprintf(output, "//\n// sound data: %s\n//\n", soundName);

    // create the struct
    fprintf(output, "const sound_t sound_%s = {\n", soundName);

    // variables to store WAV file info
    uint32_t chunkID = 0;
    uint32_t numSamples = 0;
    uint32_t sampleRate = 0;
    uint16_t bitsPerSample = 0;
    uint16_t numChannels = 0;
    uint32_t Subchunk2Size = 0;
    uint32_t rubbishBin = 0;

    // start reading from the input file
    bool done = false;
    while(!done) {

        // get 2 bytes of data
        fread(&chunkID, sizeof(uint32_t), 1, input);

        switch(chunkID) {
            case RIFF_CHUNKID:
                // seek past 'ChunkSize' and 'Format'
                fread(&rubbishBin, sizeof(uint32_t), 1, input);
                fread(&rubbishBin, sizeof(uint32_t), 1, input);

                break;

            case FMT_SUBCHUNKID:
                // seek past 'Subchunk1Size' and 'AudioFormat'
                fread(&rubbishBin, sizeof(uint32_t), 1, input);
                fread(&rubbishBin, sizeof(uint16_t), 1, input);

                // real data
                fread(&numChannels, sizeof(uint16_t), 1, input);
                fread(&sampleRate, sizeof(uint32_t), 1, input);

                // seek past 'ByteRate' and 'BlockAlign'
                fread(&rubbishBin, sizeof(uint32_t), 1, input);
                fread(&rubbishBin, sizeof(uint16_t), 1, input);

                // real data
                fread(&bitsPerSample, sizeof(uint16_t), 1, input);

                // print what we've found
                printf("\tNumber of Channels: %u\n", numChannels);
                printf("\tSample Rate: %u\n", sampleRate);
                printf("\tBits per Sample: %u\n", bitsPerSample);

                break;

            case DATA_SUBCHUNKID:
                // seek past 'Subchunk2Size'
                // fread(&rubbishBin, sizeof(uint32_t), 1, input);

                // Subchunk2Size == NumSamples * NumChannels * BitsPerSample/8
                fread(&Subchunk2Size, sizeof(uint32_t), 1, input);

                // Calculate NumSamples
                numSamples = Subchunk2Size /numChannels / (bitsPerSample/8);

                printf("\tnumSamples: %u\n", numSamples);

                // set up our file
                fprintf(output, "    .data = {");

                // parse the sound data!
                uint32_t i = 0;
                uint8_t tmp = 0;
                for (i=numSamples; i>0; i--) {
                    // read from input file
                    fread(&tmp, sizeof(uint8_t), 1, input);

                    // write to output .c file
                    if (i == 1) fprintf(output, "%d},\n", tmp);
                    else        fprintf(output, "%d,", tmp);
                }

                done = true;
                break;

            default:
                break;

        }
    }

    fprintf(output, "    .numSamples = %d,\n", numSamples);
    fprintf(output, "    .sampleRate = %d\n", sampleRate);
    fprintf(output, "};\n\n\n");

    // close our fd's
    fclose(output);
    fclose(input);

    return 0;
}

// ----------------------------------------------------------------------------
// Helper Methods
// ----------------------------------------------------------------------------

void usage() {
    printf("\nSound Converter\n\n");
    printf("usage: soundConverter [inputWAV] [soundName]\n\n");
}

// ----------------------------------------------------------------------------

bool fileExists(const char *filename) {
    struct stat buffer;
    int32_t status = stat(filename, &buffer);
    return (stat(filename, &buffer)) ? false : true;
}

// ----------------------------------------------------------------------------

void writeHeader(FILE *file) {
    fprintf(file, "/**\n");
    fprintf(file, " * Generated by soundConverter.\n");
    fprintf(file, " */\n");
    fprintf(file, "#include <stdint.h>\n\n\n");

    // struct definition
    fprintf(file, "// sound struct definition -- move this to a *.h file\n");
    fprintf(file, "typedef struct {\n");
    fprintf(file, "    uint32_t numSamples;\n");
    fprintf(file, "    uint32_t sampleRate;\n");
    fprintf(file, "    const uint32_t data[];\n");
    fprintf(file, "} sound_t;\n\n\n");
}

// ----------------------------------------------------------------------------
