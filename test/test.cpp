#include <avakar/dispatch.h>
#include <avakar/mutest.h>

mutest_case("dispatch dispatches correctly")
{
	avakar::dispatch<1>(0, [](auto v) { chk v == 0; });

	avakar::dispatch<2>(0, [](auto v) { chk v == 0; });
	avakar::dispatch<2>(1, [](auto v) { chk v == 1; });

	avakar::dispatch<0xff>(0, [](auto v) { chk v == 0; });
	avakar::dispatch<0xff>(1, [](auto v) { chk v == 1; });
	avakar::dispatch<0xff>(0xfe, [](auto v) { chk v == 0xfe; });

	avakar::dispatch<0x100>(0, [](auto v) { chk v == 0; });
	avakar::dispatch<0x100>(1, [](auto v) { chk v == 1; });
	avakar::dispatch<0x100>(0xff, [](auto v) { chk v == 0xff; });

	avakar::dispatch<0x101>(0, [](auto v) { chk v == 0; });
	avakar::dispatch<0x101>(1, [](auto v) { chk v == 1; });
	avakar::dispatch<0x101>(0xff, [](auto v) { chk v == 0xff; });
	avakar::dispatch<0x101>(0x100, [](auto v) { chk v == 0x100; });
}

mutest_case("dispatch forwards return types correctly")
{
	chk std::same_as<
		decltype(avakar::dispatch<2>(0, [](auto) {})),
		void
		>;

	chk std::same_as<
		decltype(avakar::dispatch<2>(0, [](auto) { return 1; })),
		int
		>;

	int i;
	chk std::same_as<
		decltype(avakar::dispatch<2>(0, [&](auto) -> int & { return i; })),
		int &
		>;
}

mutest_case("dispatch traits")
{
	chk avakar::is_dispatchable_v<2, decltype([](auto){})>;
	chk avakar::is_dispatchable_v<1, decltype([](std::integral_constant<std::size_t, 0>){})>;

	chk !avakar::is_dispatchable_v<2, decltype([]{})>;
	chk !avakar::is_dispatchable_v<2, decltype([](std::integral_constant<std::size_t, 0>){})>;
	chk !avakar::is_dispatchable_v<2, decltype([](auto v){ return v; })>;

	chk avakar::is_nothrow_dispatchable_v<2, decltype([](auto) noexcept {})>;
	chk !avakar::is_nothrow_dispatchable_v<2, decltype([](auto){})>;

	chk !avakar::is_nothrow_dispatchable_v<2, decltype([]{})>;

	chk noexcept(avakar::dispatch<2>(0, [](auto) noexcept {}));
	chk !noexcept(avakar::dispatch<2>(0, [](auto){}));
}
