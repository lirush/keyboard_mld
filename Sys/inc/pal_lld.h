#ifndef _PAL_LLD_H
#define _PAL_LLD_H

/**
* @brief   Type of an I/O line.
*/
typedef unsigned int ioline_t;

/**
* @brief   Digital I/O port sized unsigned type.
*/
typedef unsigned int ioportmask_t;

/**
* @brief   Forms a line identifier.
* @details A port/pad pair are encoded into an @p ioline_t type. The encoding
*          of this type is platform-dependent.
*/
#define PAL_LINE(port, pad) ((ioline_t)((uint32_t)(port)) | ((uint32_t)(pad)))

/**
* @brief   Decodes a port identifier from a line identifier.
*/
#define PAL_PORT(line) ((MDR_PORT_TypeDef *)(((uint32_t)(line)) & 0xFFFFFFF0U))

/**
* @brief   Decodes a pad identifier from a line identifier.
*/
#define PAL_PAD(line) ((uint32_t)((uint32_t)(line) & 0x0000000FU))

#endif	//_PAL_LLD_H
