#include "registration_hash.h"
#include "internals.h"


/*
* DJBX33A (Daniel J. Bernstein, Times 33 with Addition)
*
* This is Daniel J. Bernstein's popular `times 33' hash function as
* posted by him years ago on comp.lang.c. It basically uses a function
* like ``hash(i) = hash(i-1) * 33 + str[i]''. This is one of the best
* known hash functions for strings. Because it is both computed very
* fast and distributes very well.
*
* The magic of number 33, i.e. why it works better than many other
* constants, prime or not, has never been adequately explained by
* anyone. So I try an explanation: if one experimentally tests all
* multipliers between 1 and 256 (as RSE did now) one detects that even
* numbers are not useable at all. The remaining 128 odd numbers
* (except for the number 1) work more or less all equally well. They
* all distribute in an acceptable way and this way fill a hash table
* with an average percent of approx. 86%.
*
* If one compares the Chi^2 values of the variants, the number 33 not
* even has the best value. But the number 33 and a few other equally
* good numbers like 17, 31, 63, 127 and 129 have nevertheless a great
* advantage to the remaining numbers in the large set of possible
* multipliers: their multiply operation can be replaced by a faster
* operation based on just one shift plus either a single addition
* or subtraction operation. And because a hash function has to both
* distribute good _and_ has to be very fast to compute, those few
* numbers should be preferred and seems to be the reason why Daniel J.
* Bernstein also preferred it.
*
*
* -- Ralf S. Engelschall <rse@engelschall.com>
*/
static uint32_t djb_hash(uint8_t *str, uint32_t len)
{
    uint32_t hash = 5381;
    uint32_t i    = 0;

    for (i = 0; i < len; str++, i++) {
        hash = ((hash << 5) + hash) + (*str);
    }

    return hash;
}

uint32_t registration_hash(uint8_t *str, uint32_t len)
{
    return djb_hash(str, len);
}


uint32_t registration_hash_context(lwm2m_context_t *context)
{

    int payload_length = object_getRegisterPayloadBufferLength(context);
    if (payload_length <= 0) {
        lwm2m_printf("%s payload_length(%d) < 0", __PRETTY_FUNCTION__, payload_length);
        return 0;
    }

    uint8_t *payload = (uint8_t *)lwm2m_malloc(payload_length * sizeof(uint8_t));
    if (payload == NULL) {
        lwm2m_printf("%s payload == NULL", __PRETTY_FUNCTION__);
        return 0;
    }

    int res = object_getRegisterPayload(context, payload, payload_length);
    if (res <= 0) {
        lwm2m_printf("%s res(%d) < 0", __PRETTY_FUNCTION__, res);
        return 0;
    }

    uint32_t hash = registration_hash(payload, payload_length);
    lwm2m_free(payload);

    return hash;

}