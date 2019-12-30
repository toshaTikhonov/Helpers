#include <stdio.h>
#include "h_mfdfile.h"

static h_mf_classic_tag mtKeys;
static h_mf_classic_tag mtDump;

int mfdread(char* file_name, h_mf_classic_tag mt_dump,unsigned char uiBlocks)
{
    FILE *pfDump = fopen(file_name, "rb");
    if(pfDump == NULL)
        return -1;
    if (fread(&mtDump, 1, (uiBlocks + 1) * sizeof(h_mf_classic_block), pfDump) != (uiBlocks + 1) * sizeof(h_mf_classic_block)) {
        fclose(pfDump);
        return -1;
    }
    fclose(pfDump);
    return 0;
}
