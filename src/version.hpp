// Copyright (c) 2012-2018, The CryptoNote developers, The Bytecoin developers.
// Copyright (c) 2018, The Catalyst developers.
// Licensed under the GNU Lesser General Public License. See LICENSE for details.

#pragma once

// defines are for Windows resource compiler
#define catalyst_VERSION_WINDOWS_COMMA 3, 18, 5, 24
#define catalyst_VERSION_STRING "0.0.1" // we will need to change this for the first release

#ifndef RC_INVOKED  // Windows resource compiler

namespace catalyst {
inline const char *app_version() { return catalyst_VERSION_STRING; }
}

#endif
