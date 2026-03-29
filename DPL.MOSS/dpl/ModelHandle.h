#pragma once

#define MODELHANDLE16_TO_MODELHANDLE32(X) (X & 0xfc00) << 6 | X & 0x3ff 