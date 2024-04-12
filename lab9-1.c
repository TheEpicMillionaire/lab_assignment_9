#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

struct HashType
{
    int size;
    struct RecordType** array;
};

// Compute the hash function
int hash(int x)
{
    return x % 67;
}


// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);

		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    for (i = 0; i < hashSz; ++i)
    {
        if (pHashArray->array[i] != NULL)
        {
            // If the index is occupied with a record, print it
            printf("ID: %d = %d, %c, %d\n", i, pHashArray->array[i]->id, pHashArray->array[i]->name, pHashArray->array[i]->order);
        }
    }
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    int hashSize = 67;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType hashArray;
    hashArray.size = hashSize;
    hashArray.array = (struct RecordType**)malloc(sizeof(struct RecordType*) * hashSize);
    if (hashArray.array == NULL)
    {
        printf("Hash array memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < hashSize; ++i)
    {
        hashArray.array[i] = NULL;
    }

    for (int i = 0; i < recordSz; ++i)
    {
        int index = hash(pRecords[i].id);
        hashArray.array[index] = &pRecords[i];
    }

    displayRecordsInHash(&hashArray, hashSize);

    free(pRecords);
    free(hashArray.array);

    return 0;
}
