#include "stdafx.h"
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2016 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <cstdlib>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#ifdef WIN32
#pragma comment(lib,"libeay32.lib")
#pragma comment(lib, "ssleay32.lib")
#endif

enum { max_length = 1024 };

int g_count = -1;

template<typename Socket = boost::asio::ip::tcp::socket>
class client
{
public:
	client(boost::asio::io_service& io_service,
		boost::asio::ssl::context& context,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		: socket_(io_service, context)
	{
//		socket_.set_verify_mode(boost::asio::ssl::verify_peer);
//		socket_.set_verify_callback(
//			boost::bind(&client::verify_certificate, this, _1, _2));

		boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
			boost::bind(&client::handle_connect_ssl, this,
				boost::asio::placeholders::error));

	}
	client(boost::asio::io_service& io_service,
		boost::asio::ip::tcp::resolver::iterator endpoint_iterator)
		: socket_(io_service)
	{
		//		socket_.set_verify_mode(boost::asio::ssl::verify_peer);
		//		socket_.set_verify_callback(
		//			boost::bind(&client::verify_certificate, this, _1, _2));

		boost::asio::async_connect(socket_.lowest_layer(), endpoint_iterator,
			boost::bind(&client::handle_connect, this,
				boost::asio::placeholders::error));
	}
	bool verify_certificate(bool preverified,
		boost::asio::ssl::verify_context& ctx)
	{
		// The verify callback can be used to check whether the certificate that is
		// being presented is valid for the peer. For example, RFC 2818 describes
		// the steps involved in doing this for HTTPS. Consult the OpenSSL
		// documentation for more details. Note that the callback is called once
		// for each certificate in the certificate chain, starting from the root
		// certificate authority.

		// In this example we will simply print the certificate's subject name.
		char subject_name[256];
		X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
		X509_NAME_oneline(X509_get_subject_name(cert), subject_name, 256);
		std::cout << "Verifying " << subject_name << "\n";

		return preverified;
	}
	void handle_connect_ssl(const boost::system::error_code& error)
	{
		if (!error)
		{

			socket_.async_handshake(boost::asio::ssl::stream_base::client,
				boost::bind(&client::handle_handshake, this,
					boost::asio::placeholders::error));

		}
		else
		{
			std::cout << "Connect failed: " << error.message() << "\n";
		}
	}
	void handle_connect(const boost::system::error_code& error)
	{
		if (!error)
		{

			wait_input_and_send();

		}
		else
		{
			std::cout << "Connect failed: " << error.message() << "\n";
		}
	}

	void handle_handshake(const boost::system::error_code& error)
	{
		if (!error)
		{
			wait_input_and_send();
		}
		else
		{
			std::cout << "Handshake failed: " << error.message() << "\n";
		}
	}

	void handle_write(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			socket_.async_read_some(
				boost::asio::buffer(reply_, sizeof(reply_)),
				boost::bind(&client::handle_read, this,
					boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
		}
		else
		{
			std::cout << "Write failed: " << error.message() << "\n";
		}
	}

	void handle_read(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		if (!error)
		{
			std::cout << "Reply: ";
			std::cout.write(&reply_[2], bytes_transferred-2);
			std::cout << "\n";
			if(g_count < 0 || ++send_count_ < g_count)
				wait_input_and_send();
		}
		else
		{
			std::cout << "Read failed: " << error.message() << "\n";
		}
	}

private:
//	boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_;
	Socket socket_;
	char request_[max_length];
	char reply_[max_length];
	int  send_count_{ 0 };

	void wait_input_and_send()
	{
		std::cout << "Enter message: ";
		//std::cin.getline(&request_[2], max_length);
		strcpy(&request_[2], "abcdef");
		std::cout << (char*)&request_[2] << std::endl;
		if (request_[2] == 0)
		{
			request_[2] = '0';
			request_[3] = '\0';
		}
		size_t request_length = strlen(&request_[2]) + sizeof(int16_t);
		*((int16_t*)request_) = htons(request_length);

		boost::asio::async_write(socket_,
			boost::asio::buffer(request_, request_length),
			boost::bind(&client::handle_write, this,
				boost::asio::placeholders::error,
				boost::asio::placeholders::bytes_transferred));
	}
};

int main(int argc, char* argv[])
{
	try
	{
		if (argc < 3)
		{
			std::cerr << "Usage: client <host> <port> <SSL> <count>\n";
			return 1;
		}
		if (argc >= 5)
		{
			g_count = atoi(argv[4]);
			if (g_count <= 0 || g_count > 10000)
				g_count = 100;
		}
		boost::asio::io_service io_service;

		boost::asio::ip::tcp::resolver resolver(io_service);
		boost::asio::ip::tcp::resolver::query query(argv[1], argv[2]);
		boost::asio::ip::tcp::resolver::iterator iterator = resolver.resolve(query);

		bool use_ssl = true;
		if (argc >= 4)
			 use_ssl = (atoi(argv[3]) != 0);

		if (use_ssl)
		{
			boost::asio::ssl::context ctx(boost::asio::ssl::context::sslv23_client);
			//		ctx.load_verify_file("ca.pem");
			ctx.set_options(boost::asio::ssl::context::default_workarounds | boost::asio::ssl::context::no_sslv2 | boost::asio::ssl::context::single_dh_use);
			//	client.context().set_verify_mode(boost::asio::ssl::context::verify_peer | boost::asio::ssl::context::verify_fail_if_no_peer_cert);
			//	client.context().load_verify_file("certs/server.crt");
			ctx.use_certificate_chain_file("client_certs/server.crt");
			ctx.use_private_key_file("client_certs/server.key", boost::asio::ssl::context::pem);
			ctx.use_tmp_dh_file("client_certs/dh1024.pem");
			client<boost::asio::ssl::stream<boost::asio::ip::tcp::socket> > c(io_service, ctx, iterator);
			io_service.run();
		}
		else
		{
			client<boost::asio::ip::tcp::socket> c(io_service, iterator);
			io_service.run();
		}
		
	}
	catch (std::exception& e)
	{
		std::cerr << "Exception: " << e.what() << "\n";
	}

	return 0;
}
