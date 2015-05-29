#ifndef CHALLENGE_NONCOPYABLE_HPP
#define CHALLENGE_NONCOPYABLE_HPP

//TODO(mate): Laci f�le?
namespace Challenge
{
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

} //namespace Challenge
#endif // !#define CHALLENGE_NONCOPYABLE_HPP

