#ifndef CHALLENGE_NONCOPYABLE_HPP
#define CHALLENGE_NONCOPYABLE_HPP

class NonCopyable
{
protected:
	NonCopyable() {}
private:
	NonCopyable(const NonCopyable&) = delete;
	NonCopyable& operator=(const NonCopyable&) = delete;

	NonCopyable(const NonCopyable&&) = delete;
	NonCopyable& operator=(const NonCopyable&&) = delete;
};

#endif // !#define CHALLENGE_NONCOPYABLE_HPP

