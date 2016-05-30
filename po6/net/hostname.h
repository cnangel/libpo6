// Copyright (c) 2012,2015, Robert Escriva
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of po6 nor the names of its contributors may be used
//       to endorse or promote products derived from this software without
//       specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef po6_net_hostname_h_
#define po6_net_hostname_h_

// STL
#include <iostream>

// po6
#include <po6/net/location.h>
#include <po6/net/socket.h>

namespace po6
{
namespace net
{

class hostname
{
public:
	hostname();
	hostname(const char *_address, in_port_t _port);
	explicit hostname(const location &);
	hostname(const hostname &other);
	~hostname() throw ();

public:
	location connect(int domain, int type, int protocol, socket *sock) const;
	// non-throwing, non-connecting version
	location lookup(int type, int protocol) const;

public:
	bool operator < (const hostname &rhs) const;
	bool operator <= (const hostname &rhs) const;
	bool operator == (const hostname &rhs) const;
	bool operator != (const hostname &rhs) const;
	bool operator >= (const hostname &rhs) const;
	bool operator > (const hostname &rhs) const;

public:
	std::string address;
	in_port_t port;

private:
	int compare(const hostname &rhs) const;
};

std::ostream &
operator << (std::ostream &lhs, const hostname &rhs);

} // namespace net
} // namespace po6

#endif // po6_net_hostname_h_
