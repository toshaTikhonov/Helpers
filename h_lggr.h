#ifndef __H_LGGR_H__
#define __H_LGGR_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void h_lggr_print_memory(const char *psz_title, const void *p_p_data, unsigned int lsize);
void h_lggr_printf_line(const char *pszFmt, ...);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
