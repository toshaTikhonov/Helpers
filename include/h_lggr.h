#ifndef __H_LGGR_H__
#define __H_LGGR_H__

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void h_lggr_print_memory(const char *psz_title, const void *p_p_data, unsigned int lsize);
void h_lggr_printf_line(const char *pszFmt, ...);
void h_lggr_inc_level( void );
void h_lggr_dec_level( void );

int h_lggr_init(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
