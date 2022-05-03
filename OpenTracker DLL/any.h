/////////////////////////////////////////////////////////////////////////////////////////////
// C++11/C++14 any class
//
// This is a polymorphic wrapper capable of holding any type available on C++17 and above or boost but not on C++11 or C++14. (It is loosely based on boost::any)
// In particular, this is useful when you want to store a heterogeneous collection, such as vector<any>.
//
// Code is taken from https://codereview.stackexchange.com/questions/20058/c11-any-class and suggested code improvements from an unknow author by now,
// As the author stated in its contribution: this code is under "Public domain. You may use it any way you like without attribution."
//
/////////////////////////////////////////////////////////////////////////////////////////////


#pragma once
#include <memory>
#include <type_traits>
#include <utility>
#include <typeinfo>
#include <string>
#include <cassert>

using namespace std;

template <class T>
using StorageType = typename decay<T>::type;

struct any
{
	bool is_null() const { return !ptr; }
	bool not_null() const { return ptr; }

	template<typename U> any(U&& value)
		: ptr(new Derived<StorageType<U>>(forward<U>(value)))
	{

	}

	template <typename U>
	friend const U *any_cast(const any *) noexcept;

	template <typename U>
	friend U *any_cast(any *) noexcept;

	template<class U> bool is() const
	{
		typedef StorageType<U> T;

		auto derived = dynamic_cast<Derived<T>*> (ptr);

		return derived;
	}

	template<class U>
	StorageType<U>& as()
	{
		typedef StorageType<U> T;

		auto derived = dynamic_cast<Derived<T>*> (ptr);

		if (!derived)
			throw bad_cast();

		return derived->value;
	}

	template<class U>
	operator U()
	{
		return as<StorageType<U>>();
	}


	// C++20
	template <typename T>
	using remove_cvref_t = remove_cv_t<remove_reference_t<T>>;


	// any_cast

	class bad_any_cast : public bad_cast {
	public:
		const char *what() const noexcept {
			return "bad any cast";
		}
	};

	template <typename U>
	U any_cast(const any &anything) {
		using value_type_cvref = remove_cvref_t<U>;
		static_assert(std::is_constructible<U, const value_type_cvref &>, "program is ill-formed");
		if (auto *value = any_cast<value_type_cvref>(&anything)) {
			return static_cast<U>(*value);
		}
		else {
			throw bad_any_cast();
		}
	}

	template <typename U>
	U any_cast(any &anything) {
		using value_type_cvref = remove_cvref_t<U>;
		static_assert(std::is_constructible<U, value_type_cvref &>, "program is ill-formed");
		if (auto *value = any_cast<value_type_cvref>(&anything)) {
			return static_cast<U>(*value);
		}
		else {
			throw bad_any_cast();
		}
	}

	template <typename U>
	U any_cast(any &&anything) {
		using value_type_cvref = remove_cvref_t<U>;
		static_assert(std::is_constructible<U, value_type_cvref>, "program is ill-formed");
		if (auto *value = any_cast<value_type_cvref>(&anything)) {
			return static_cast<U>(std::move(*value));
		}
		else {
			throw bad_any_cast();
		}
	}

	template <typename U>
	const U *any_cast(const any *anything) noexcept {
		if (!anything) return nullptr;
		auto *storage = dynamic_cast<any::storage_impl<U> *>(anything->instance.get());
		if (!storage) return nullptr;
		return &storage->value;
	}

	template <typename U>
	U *any_cast(any *anything) noexcept {
		return const_cast<U *>(any_cast<U>(static_cast<const any *>(anything)));
	}

	// make_any

	template <typename U, typename... Args>
	any make_any(Args &&... args) {
		return any(decltype<U>, std::forward<Args>(args)...);
	}

	template <typename U, typename List, typename... Args>
	any make_any(std::initializer_list<List> list, Args &&... args) {
		return any(decltype<U>, list, std::forward<Args>(args)...);
	}


	any()
		: ptr(nullptr)
	{

	}

	any(any& that)
		: ptr(that.clone())
	{

	}

	any(any&& that)
		: ptr(that.ptr)
	{
		that.ptr = nullptr;
	}

	any(const any& that)
		: ptr(that.clone())
	{

	}

	any(const any&& that)
		: ptr(that.clone())
	{

	}

	any& operator=(const any& a)
	{
		if (ptr == a.ptr)
			return *this;

		auto old_ptr = ptr;

		ptr = a.clone();

		if (old_ptr)
			delete old_ptr;

		return *this;
	}

	any& operator=(any&& a)
	{
		if (ptr == a.ptr)
			return *this;

		swap(ptr, a.ptr);

		return *this;
	}

	~any()
	{
		delete ptr;
	}

private:
	struct Base
	{
		virtual ~Base() {}

		virtual Base* clone() const = 0;
	};

	template<typename T>
	struct Derived : Base
	{
		template<typename U> Derived(U&& value) : value(forward<U>(value)) { }

		T value;

		Base* clone() const { return new Derived<T>(value); }
	};

	Base* clone() const
	{
		if (ptr)
			return ptr->clone();
		else
			return nullptr;
	}

	Base* ptr;

	struct storage_base;

	std::unique_ptr<storage_base> instance;

	struct storage_base {
		virtual ~storage_base() = default;

		virtual const std::type_info &type() const noexcept = 0;
		virtual std::unique_ptr<storage_base> clone() const = 0;
	};

	template <typename U>
	struct storage_impl final : public storage_base {
		template <typename... Args>
		storage_impl(Args &&... args)
			: value(std::forward<Args>(args)...) {}

		const std::type_info &type() const noexcept override {
			return typeid(U);
		}

		std::unique_ptr<storage_base> clone() const override {
			return std::make_unique<storage_impl<U>>(value);
		}

		U value;
	};
};
