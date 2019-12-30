#ifndef __H_MFDFILE_H__
#define __H_MFDFILE_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#pragma pack(1)

/*
* @brief  MIFARE Classic
*/
typedef struct {
  unsigned char  abtUID[4];  // beware for 7bytes UID it goes over next fields
  unsigned char  btBCC;
  unsigned char  btSAK;      // beware it's not always exactly SAK
  unsigned char  abtATQA[2];
  unsigned char  abtManufacturer[8];
} h_mf_classic_block_manufacturer;

/*
* @brief  MIFARE Classic data block
*/
typedef struct {
  unsigned char  abtData[16];
} h_mf_classic_block_data;

/*
* @brief  MIFARE Classic block trailer
*/
typedef struct {
  unsigned char  abtKeyA[6];
  unsigned char  abtAccessBits[4];
  unsigned char  abtKeyB[6];
} h_mf_classic_block_trailer;
/*
* @brief  MIFARE Classic sector
*/
typedef union {
  h_mf_classic_block_manufacturer mbm;
  h_mf_classic_block_data mbd;
  h_mf_classic_block_trailer mbt;
} h_mf_classic_block;
/*
* @brief  MIFARE Classic card structure
*/
typedef struct {
  h_mf_classic_block amb[256];
} h_mf_classic_tag;

#pragma pack()


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
