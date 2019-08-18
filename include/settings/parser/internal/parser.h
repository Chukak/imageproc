#ifndef PARSER_H
#define PARSER_H

#include "settings/internal/types.h"
#include "execute/wrapper.h"

class Parser
{
	friend struct ParserWrapper;

protected:
	explicit Parser(int _argc, char** _argv, Wrapper* w);
	void set_image(cv::Mat& frame) noexcept;
	void set_save_path() noexcept;
	template<typename C>
	void set_process(C* o) noexcept;
	void add_error(message_t e) noexcept;
	virtual void executed_data(std::string& save, bool& finish, errors_t& errors);
	template<typename Array>
	bool find_in(Array array) noexcept;

public:
	virtual void parse() noexcept = 0;

protected:
	int argc{-1};
	char** argv{};
	int index{1};
	bool bad{false};
	std::string save{""};
	errors_t errors{};

private:
	// shared_ptr no delete. Todo: fix/update
	std::unique_ptr<Wrapper, void (*)(Wrapper*)> wrapper{nullptr, [](Wrapper*) {}};
};

template<typename C>
void Parser::set_process(C* o) noexcept
{
	wrapper->set(make_process(o));
}

template<typename Array>
bool Parser::find_in(Array array) noexcept
{
	return std::find(std::begin(array), std::end(array), argv[index]) != std::end(array);
}

struct ParserWrapper
{
	explicit ParserWrapper(std::string& s, bool& f, errors_t& e);
	void set_args(int _argc, char** _argv, Wrapper* _w);
	template<class C>
	void run() noexcept;

private:
	int argc{-1};
	char** argv{};
	Wrapper* w{nullptr};
	std::string& save;
	bool& finish;
	errors_t& errors;
};

template<class C>
void ParserWrapper::run() noexcept
{
	if(std::is_base_of_v<Parser, C>) {
		C parser(argc, argv, w);
		parser.parse();
		parser.executed_data(save, finish, errors);
	}
}

#endif // PARSER_H
