// Copyright (c) 2011, Robert Escriva
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

#ifndef po6_error_h_
#define po6_error_h_

// C
#include <stdlib.h>
#include <string.h>

// C++
#include <iostream>
#include <exception>
#include <stdexcept>

namespace po6
{

#define PO6_ERROR_MSG_LEN 1024

class error : public std::exception
{
public:
	error();
	error(int num);
	error(int num, const char *msg);
	error(const error &e);
	~error() throw ();

public:
	const char *what() const throw ();

public:
	operator int () const;
	error &operator = (const error &rhs);

private:
	void use_strerror();

private:
	int m_errno;
	char m_msg[PO6_ERROR_MSG_LEN];
};

inline
error :: error()
	: m_errno(0)
	, m_msg()
{
	use_strerror();
}

inline
error :: error(int num)
	: m_errno(num)
	, m_msg()
{
	use_strerror();
}

inline
error :: error(int num, const char *msg)
	: m_errno(num)
	, m_msg()
{
	strncpy(m_msg, msg, PO6_ERROR_MSG_LEN);
	m_msg[PO6_ERROR_MSG_LEN - 1] = '\0';
}

inline
error :: error(const error &e)
	: m_errno(e.m_errno)
	, m_msg()
{
	strncpy(m_msg, e.m_msg, PO6_ERROR_MSG_LEN);
}

inline
error :: ~error() throw ()
{
}

inline const char *
error :: what() const throw ()
{
	return m_msg;
}

inline
error :: operator int () const
{
	return m_errno;
}

inline error &
error :: operator = (const error &rhs)
{
	m_errno = rhs.m_errno;
	strncpy(m_msg, rhs.m_msg, PO6_ERROR_MSG_LEN);
	return *this;
}

#ifndef _MSC_VER
inline void
error :: use_strerror()
{
#ifdef _GNU_SOURCE
	if (_GNU_SOURCE)
	{
		strncpy(m_msg, strerror_r(m_errno, m_msg, PO6_ERROR_MSG_LEN), PO6_ERROR_MSG_LEN);
		m_msg[PO6_ERROR_MSG_LEN - 1] = '\0';
	}
	else
	{
#endif
		strerror_r(m_errno, m_msg, PO6_ERROR_MSG_LEN);
		m_msg[PO6_ERROR_MSG_LEN - 1] = '\0';
#ifdef _GNU_SOURCE
	}
#endif
}

#else /* _MSC_VER */
inline void
error :: use_strerror()
{
	char *msg = strerror(m_errno);
	size_t l = strlen(m_msg);
	if (l >= PO6_ERROR_MSG_LEN)
	{
		if (PO6_ERROR_MSG_LEN)
		{
			memcpy(m_msg, msg, PO6_ERROR_MSG_LEN - 1);
		}
	}
	else
	{
		memcpy(m_msg, msg, l + 1);
	}
}
#endif /* MSC_VER */

#undef PO6_ERROR_MSG_LEN

} // namespace po6

#endif // po6_error_h_
