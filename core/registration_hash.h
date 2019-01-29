#ifndef _REGISTRATION_HASH_H_
#define _REGISTRATION_HASH_H_

#include "liblwm2m.h"

uint32_t registration_hash_context(lwm2m_context_t *context);
uint32_t registration_hash(uint8_t *str, uint32_t len);

#endif

