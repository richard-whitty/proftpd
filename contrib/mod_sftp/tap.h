/*
 * ProFTPD - mod_sftp traffic analysis protection
 * Copyright (c) 2008-2009 TJ Saunders
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307, USA.
 *
 * As a special exemption, TJ Saunders and other respective copyright holders
 * give permission to link this program with OpenSSL, and distribute the
 * resulting executable, without including the source code for OpenSSL in the
 * source distribution.
 *
 * $Id: tap.h,v 1.3 2009-08-25 05:07:14 castaglia Exp $
 */

#include "mod_sftp.h"

#ifndef MOD_SFTP_TAP_H
#define MOD_SFTP_TAP_H

int sftp_tap_have_policy(const char *);

/* May send an SSH2_MSG_IGNORE packet of random length, filled with random
 * data to the client, depending on the selected policy.  These messages can
 * be injected into the SSH session in order to make traffic analysis harder.
 * Returns -1 if there was an error while sending the packet.
 */
int sftp_tap_send_packet(void);

/* Sets the traffic analysis protection (TAP) policy.  Returns 0 if the given
 * policy is acceptable, -1 otherwise.
 *
 * The list of policies is:
 *
 *  "none" - send no SSH2_MSG_IGNORE packets
 *
 *  "low" - 1 in 1000 chance of sending SSH2_MSG_IGNORE, with lengths of
 *          64 to 256 bytes of random data.
 *
 *  "medium" - 1 in 100 chance of sending SSH2_MSG_IGNORE, with lengths of
 *             32 to 768 bytes of random data.
 *
 *  "high" - 1 in 10 chance of sending SSH2_MSG_IGNORE, with lengths of
 *           16 to 2048 bytes of random data.
 *
 *  "paranoid" - always send SSH2_MSG_IGNORE packets, of lengths up to 8KB.
 *
 * Note that there is an additional TAP policy called 'cbc-mode'.  This
 * policy is automatically used if the negotiated server-to-client cipher
 * is any of the CBC ciphers.  The purpose of the 'cbc-mode' TAP policy is
 * to implement the mitigation of the Rogaway CBC mode attack (see RFC4251,
 * Section 9.3.1) via the use of IGNORE packets.  The use of the 'cbc-mode'
 * policy is hardcoded, and will override any configured TAP policy.
 */
int sftp_tap_set_policy(const char *);

#endif
