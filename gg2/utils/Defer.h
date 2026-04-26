#pragma once

template<typename F>
struct Defer { F f; ~Defer() { f(); } };

template<typename F>
Defer<F> makeDefer(F f) { return {f}; }

#define defer(code) auto _defer##__LINE__ = makeDefer([&]{ code; })
