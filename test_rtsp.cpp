#include "http_parser.h"

#include <iostream>
#include <string>

std::string options = "OPTIONS * RTSP/1.0\r\nCSeq: 1\r\nRequire: implicit-play\r\nProxy-Require: gzipped-messages\r\n\r\n";
std::string describe = "DESCRIBE rtsp://server.example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nAccept: application/sdp, application/rtsl, application/mheg\r\n\r\n";
std::string setup = "SETUP rtsp://example.com/foo/bar/baz.rm RTSP/1.0\r\nCSeq: 312\r\nTransport: RTP/AVP;unicast;client_port=4588-4589\r\n\r\n";
std::string play  = "PLAY rtsp://audio.example.com/audio RTSP/1.0\r\nCSeq: 312\r\nSession: 12345678\r\nRange: npt=20-25\r\n\r\n";
std::string pause = "PAUSE rtsp://example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nSession: 12345678\r\n\r\n";
std::string teardown = "TEARDOWN rtsp://example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nSession: 12345678\r\n\r\n";
std::string get_parameter = "GET_PARAMETER rtsp://example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nSession: 12345678\r\nContent-Length: 16\r\n\r\n";
std::string set_parameter = "SET_PARAMETER rtsp://example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nSession: 12345678\r\nContent-Length: 20\r\n\r\n";
std::string redirect = "REDIRECT rtsp://example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nSession: 12345678\r\nLocation: rtsp://bigserver.com:8001\r\n\r\n";
std::string record = "RECORD rtsp://example.com/fizzle/foo RTSP/1.0\r\nCSeq: 312\r\nSession: 12345678\r\nConference: 128.16.64.19/32492374\r\n\r\n";
std::string response = "RTSP/1.0 200 OK\r\nCSeq: 312\r\nDate: 23 Jan 1997 15:35:06 GMT\r\nContent-Type: application/sdp\r\nContent-Length: 394\r\n\r\n";
std::string sdp = "v = 0\r\n"
				"o = mhandley 2890844526 2890842807 IN IP4 126.16.64.4\r\n"
				"s = SDP Seminar\r\n"
				"i = A Seminar on the session description protocol\r\n"
				"u = http://www.cs.ucl.ac.uk/staff/M.Handley/sdp.03.ps\r\n"
				"e = mjh@isi.edu(Mark Handley)\r\n"
				"c = IN IP4 224.2.17.12 / 127\r\n"
				"t = 2873397496 2873404696\r\n"
				"a = recvonly\r\n"
				"m = audio 3456 RTP / AVP 0\r\n"
				"m = video 2232 RTP / AVP 31\r\n"
				"m = whiteboard 32416 UDP WB\r\n"
				"a = orient:portrait\r\n";


int onurl(http_parser* parser, const char* at, size_t Length)
{
	std::cout << "url:" << std::string{ at,Length } << std::endl;
	return 0;
}

int onStatus(http_parser* parser, const char* at, size_t Length)
{
	std::cout <<" status:" << std::string{ at,Length } << std::endl;
	return 0;
}

int onHeaderField(http_parser* parser, const char* at, size_t Length)
{
	std::cout <<" header field:" << std::string{ at,Length } << std::endl;
	return 0;
}

int onHeaderValue(http_parser* parser, const char* at, size_t Length)
{
	std::cout << "header value:" << std::string{ at,Length } << std::endl;
	return 0;
}

int onBody(http_parser* parser, const char* at, size_t Length)
{
	std::cout << "body: " << std::string{ at,Length } << std::endl;
	return 0;
}

int onHeaderCompleted(http_parser* parser)
{
	std::cout << "head complted" << std::endl;
	return 0;
}


int onMessageCompleted(http_parser* parser)
{
	std::cout << "message complted" << std::endl;
	return 0;
}

void testOptions()
{
	std::cout << "==========test options===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, options.c_str(), options.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test options===========" << std::endl;
}

void testDescribe()
{
	std::cout << "==========test describe===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;
	
	int ret = http_parser_execute(&parser, &setting, describe.c_str(), describe.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;

	std::cout << "==========test describe===========" << std::endl;
}

void testSetup()
{
	std::cout << "==========test setup===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, setup.c_str(), setup.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test setup===========" << std::endl;
}

void testPlay()
{
	std::cout << "==========test play===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;
	
	int ret = http_parser_execute(&parser, &setting, play.c_str(), play.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test play===========" << std::endl;
}

void testPause()
{
	std::cout << "==========test pause===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, pause.c_str(), pause.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test pause===========" << std::endl;
}

void testTeardown()
{
	std::cout << "==========test teardown===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;
	int ret = http_parser_execute(&parser, &setting, teardown.c_str(), teardown.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test teardown===========" << std::endl;
}

void testSetParameter()
{
	std::cout << "==========test setparameter===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_BOTH);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, set_parameter.c_str(), set_parameter.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test setparameter===========" << std::endl;
}

void testGetParameter()
{
	std::cout << "==========test getparameter===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, get_parameter.c_str(), get_parameter.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test getparameter===========" << std::endl;
}

void testRedirect()
{
	std::cout << "==========test redirect===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, redirect.c_str(), redirect.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;
	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;

	std::cout << "==========test redirect===========" << std::endl;
}

void testRecord()
{
	std::cout << "==========test record===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_REQUEST);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, record.c_str(), record.size());

	std::cout << parser.method << std::endl;
	std::cout << http_method_str((http_method)parser.method) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;

	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;
	std::cout << "==========test record===========" << std::endl;
}

void testResponse()
{
	response += sdp;
	std::cout << "==========test response===========" << std::endl;
	http_parser_settings setting;
	http_parser parser;
	http_parser_init(&parser, HTTP_RESPONSE);
	http_parser_settings_init(&setting);
	setting.on_url = onurl;
	setting.on_status = onStatus;
	setting.on_header_field = onHeaderField;
	setting.on_header_value = onHeaderValue;
	setting.on_body = onBody;
	setting.on_headers_complete = onHeaderCompleted;
	setting.on_message_complete = onMessageCompleted;

	int ret = http_parser_execute(&parser, &setting, response.c_str(), response.size());

	std::cout << parser.status_code << std::endl;
	std::cout << http_status_str((http_status)parser.status_code) << std::endl;
	std::cout << ret << std::endl;

	std::cout << parser.http_errno << std::endl;
	std::cout << http_errno_name(HTTP_PARSER_ERRNO(&parser)) << std::endl;

	std::cout << "==========test response===========" << std::endl;
}

int main()
{
	get_parameter += "packets_received";
	set_parameter += "barparam: barstuff";
	testOptions();
	testDescribe();
	testSetup();
	testPlay();
	testPause();
	testTeardown();
	testSetParameter();
	testGetParameter();
	testRedirect();
	testRecord();
	testResponse();
}