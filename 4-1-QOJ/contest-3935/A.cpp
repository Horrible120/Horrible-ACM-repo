#include <bits/extc++.h>

using i64 = long long;

#define OOO print(">>>>");	//调试标识
#define H_test(x) println("---> {} <---",x);	//调试输出

using namespace std;
using namespace __gnu_pbds;

typedef long long ll;
typedef uint64_t ull;
template <typename T> using vct = vector<T>;
template <typename T> using v2ct = vector<vector<T>>;

template <typename T, typename Compare = std::less<T>>
using oset = tree<T, null_type, Compare, rb_tree_tag, tree_order_statistics_node_update>;

const ll INF = 4e18, Mod = 1e9+7;
mt19937_64 rnd( (uintptr_t)(char*)(&INF)+time(0) );

ll tt=1;

#line 2 "convolution_v4.cpp"

#ifndef FASTIO_UNSAFE_BLOCK_LOG
#define FASTIO_UNSAFE_BLOCK_LOG 12
#endif

#line 2 "ntt998.hpp"

#if defined(__GNUC__) && !defined(__clang__) && \
(defined(__x86_64__) || defined(__i386__))
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#elif defined(__clang__) && \
(defined(__x86_64__) || defined(__i386__))
#pragma clang attribute push( \
__attribute__((target("avx2,bmi,bmi2,lzcnt,popcnt,ssse3"))), \
	apply_to = function)
#endif

#include <bits/stdc++.h>
#include <immintrin.h>

#line 1 "math/modint998.hpp"



#line 7 "math/modint998.hpp"
#include <type_traits>

struct modint998 {
	using u32 = std::uint32_t;
	using i32 = std::int32_t;
	using u64 = std::uint64_t;
	
	static constexpr u32 MOD = 998244353u;
	static constexpr u32 MOD2 = MOD * 2;
	static constexpr u32 primitive_root = 3;
	static constexpr int max_power_of_two = 23;
	
private:
	static constexpr u32 R = 3296722945u;
	static constexpr u32 N2 = 932051910u;
	
	struct montgomery_tag {};
	
	constexpr modint998(u32 x, montgomery_tag) : a(x) {}
	
	static constexpr u32 reduce(u64 x) {
		return static_cast<u32>(
			(x + u64(static_cast<u32>(x) * u32(-R)) * MOD) >> 32
			);
	}
	
public:
	u32 a;
	
	static_assert(MOD < (u32(1) << 30));
	static_assert((MOD & 1) != 0);
	static_assert(R * MOD == 1);
	
	constexpr modint998() : a(0) {}
	
	template <class T, std::enable_if_t<std::is_integral_v<T> &&
	std::is_signed_v<T>, int> = 0>
	constexpr modint998(T x) : a(0) {
		const std::int64_t y =
		static_cast<std::int64_t>(x) % std::int64_t(MOD) + MOD;
		a = reduce(u64(y) * N2);
	}
	
	template <class T, std::enable_if_t<std::is_integral_v<T> &&
	std::is_unsigned_v<T>, int> = 0>
	constexpr modint998(T x)
	: a(reduce(((u64(x) % MOD) + MOD) * N2)) {}
	
	static constexpr modint998 raw(u32 x) {
		return modint998(reduce(u64(x) * N2), montgomery_tag{});
	}
	
	static constexpr modint998 montgomery_raw(u32 x) {
		return modint998(x, montgomery_tag{});
	}
	
	static constexpr u32 mod() { return MOD; }
	static constexpr u32 get_mod() { return MOD; }
	
	constexpr u32 val() const {
		const u32 x = reduce(a);
		return x >= MOD ? x - MOD : x;
	}
	
	constexpr u32 get() const { return val(); }
	
	constexpr modint998& operator+=(const modint998& rhs) {
		a += rhs.a - MOD2;
		if (i32(a) < 0) a += MOD2;
		return *this;
	}
	
	constexpr modint998& operator-=(const modint998& rhs) {
		a -= rhs.a;
		if (i32(a) < 0) a += MOD2;
		return *this;
	}
	
	constexpr modint998& operator*=(const modint998& rhs) {
		a = reduce(u64(a) * rhs.a);
		return *this;
	}
	
	constexpr modint998& operator/=(const modint998& rhs) {
		return *this *= rhs.inv();
	}
	
	constexpr modint998 operator+() const { return *this; }
	constexpr modint998 operator-() const { return modint998() - *this; }
	
	friend constexpr modint998 operator+(modint998 lhs,
		const modint998& rhs) {
			return lhs += rhs;
		}
	
	friend constexpr modint998 operator-(modint998 lhs,
		const modint998& rhs) {
			return lhs -= rhs;
		}
	
	friend constexpr modint998 operator*(modint998 lhs,
		const modint998& rhs) {
			return lhs *= rhs;
		}
	
	friend constexpr modint998 operator/(modint998 lhs,
		const modint998& rhs) {
			return lhs /= rhs;
		}
	
	friend constexpr bool operator==(const modint998& lhs,
		const modint998& rhs) {
			const u32 x = lhs.a >= MOD ? lhs.a - MOD : lhs.a;
			const u32 y = rhs.a >= MOD ? rhs.a - MOD : rhs.a;
			return x == y;
		}
	
	friend constexpr bool operator!=(const modint998& lhs,
		const modint998& rhs) {
			return !(lhs == rhs);
		}
	
	constexpr modint998& operator++() {
		return *this += raw(1);
	}
	
	constexpr modint998 operator++(int) {
		modint998 old = *this;
		++*this;
		return old;
	}
	
	constexpr modint998& operator--() {
		return *this -= raw(1);
	}
	
	constexpr modint998 operator--(int) {
		modint998 old = *this;
		--*this;
		return old;
	}
	
	constexpr modint998 pow(u64 exponent) const {
		modint998 result = raw(1);
		modint998 base = *this;
		while (exponent != 0) {
			if (exponent & 1) result *= base;
			base *= base;
			exponent >>= 1;
		}
		return result;
	}
	
	constexpr modint998 inv() const {
		assert(val() != 0);
		
		const modint998 x = *this;
		modint998 a2 = x * x;
		modint998 a4 = a2 * a2;
		modint998 a8 = a4 * a4;
		modint998 a16 = a8 * a8;
		modint998 a32 = a16 * a16;
		modint998 a33 = a32 * x;
		modint998 a49 = a33 * a16;
		modint998 a82 = a49 * a33;
		modint998 a164 = a82 * a82;
		modint998 a328 = a164 * a164;
		modint998 r = a328 * a49;
		
		a2 = r * r;
		a4 = a2 * a2;
		a8 = a4 * a4;
		modint998 a9 = a8 * r;
		modint998 a18 = a9 * a9;
		r = a18 * a9;
		
		a2 = r * r;
		a4 = a2 * a2;
		a8 = a4 * a4;
		a16 = a8 * a8;
		modint998 a17 = a16 * r;
		a33 = a17 * a16;
		modint998 a66 = a33 * a33;
		modint998 a132 = a66 * a66;
		modint998 a264 = a132 * a132;
		r = a264 * a17;
		
		a2 = r * r;
		a4 = a2 * a2;
		a8 = a4 * a4;
		a16 = a8 * a8;
		a32 = a16 * a16;
		modint998 a64 = a32 * a32;
		modint998 a65 = a64 * r;
		modint998 a73 = a65 * a8;
		modint998 a138 = a73 * a65;
		modint998 a276 = a138 * a138;
		return a276 * a73;
	}
	
	constexpr modint998 inverse() const { return inv(); }
	
	friend std::ostream& operator<<(std::ostream& os, const modint998& x) {
		return os << x.val();
	}
	
	friend std::istream& operator>>(std::istream& is, modint998& x) {
		std::int64_t value;
		is >> value;
		x = modint998(value);
		return is;
	}
};

static_assert(sizeof(modint998) == 4);
static_assert(std::is_trivially_copyable_v<modint998>);

using mint998 = modint998;


#line 18 "ntt998.hpp"

#if defined(_MSC_VER)
#define EEZ_NTT998_ALWAYS_INLINE __forceinline
#define EEZ_NTT998_RESTRICT __restrict
#elif defined(__GNUC__) || defined(__clang__)
#define EEZ_NTT998_ALWAYS_INLINE inline __attribute__((always_inline))
#define EEZ_NTT998_RESTRICT __restrict__
#else
#define EEZ_NTT998_ALWAYS_INLINE inline
#define EEZ_NTT998_RESTRICT
#endif

namespace eez::ntt998{
	
	using mint = modint998;
	using u32 = std::uint32_t;
	using usize = std::size_t;
	
	inline constexpr u32 mod = mint::MOD;
	inline constexpr usize max_size = usize(1) << 23;
	inline constexpr usize naive_cutoff = 60;
	
	inline void forward(std::span<mint> a) noexcept;
	inline void inverse(std::span<mint> a) noexcept;
	
	inline std::vector<mint> convolution(std::span<const mint> a, std::span<const mint> b);
	
	inline std::vector<mint> square(std::span<const mint> a);
	
	inline std::vector<mint> convolution(const std::vector<mint>& a, const std::vector<mint>& b){
		return convolution(std::span<const mint>(a.data(), a.size()), std::span<const mint>(b.data(), b.size()));
	}
	
	inline std::vector<mint> square(const std::vector<mint>& a){
		return square(std::span<const mint>(a.data(), a.size()));
	}
	
	class workspace{
	public:
		workspace() = default;
		explicit workspace(usize n){
			reserve(n);
		}
		
		void reserve(usize n){
			if (a_.size() < n) a_.resize(n);
			if (b_.size() < n) b_.resize(n);
		}
		
		[[nodiscard]] usize capacity() const noexcept {
			return std::min(a_.size(), b_.size());
		}
		
	private:
		friend void convolution_to(std::span<const mint>, std::span<const mint>, std::span<mint>, workspace&);
		
		friend void square_to(std::span<const mint>, std::span<mint>, workspace&);
		
		std::vector<mint> a_;
		std::vector<mint> b_;
	};
	
	inline void convolution_to(std::span<const mint> a, std::span<const mint> b, std::span<mint> out, workspace& ws);
	
	inline void square_to(std::span<const mint> a, std::span<mint> out, workspace& ws);
	
	
	class frequency_buffer{
	public:
		frequency_buffer() = default;
		
		[[nodiscard]] usize size() const noexcept {
			return data_.size();
		}
		
	private:
		friend void forward_to(std::span<const mint>, frequency_buffer&, usize);
		
		friend void pointwise_multiply(frequency_buffer&, const frequency_buffer&);
		
		friend void pointwise_square(frequency_buffer&);
		
		friend void inverse_to(frequency_buffer&, std::span<mint>);
		
		std::vector<mint> data_;
	};
	
	inline void forward_to(std::span<const mint> src, frequency_buffer& dst, usize n);
	
	inline void pointwise_multiply(frequency_buffer& lhs, const frequency_buffer& rhs);
	
	inline void pointwise_square(frequency_buffer& a);
	
	inline void inverse_to(frequency_buffer& src, std::span<mint> out);
	
	constexpr usize convolution_size(usize n, usize m) noexcept {
		return n && m ? n + m - 1 : 0;
	}
	
	constexpr usize transform_size(usize n, usize m) noexcept {
		if (!n || !m) return 0;
		if (n > max_size || m > max_size) return 0;
		if (n > max_size - m + 1) return 0;
		
		const usize z = n + m - 1;
		usize x = 1;
		while (x < z) x <<= 1;
		return x;
	}
	
	constexpr bool valid_ntt_size(usize n) noexcept {
		return n != 0 && (n & (n - 1)) == 0 && n <= max_size;
	}
	
	namespace detail{
		
		using word = u32;
		using u64 = std::uint64_t;
		
		inline constexpr word mod = mint::MOD;
		inline constexpr word mod2 = 2 * mod;
		inline constexpr unsigned max_log = 23;
		
		inline constexpr word montgomery_ninv = 998244351u;
		inline constexpr word montgomery_one = mint::raw(1).a;
		
		static_assert(mod < (word(1) << 30));
		static_assert(word(mod * montgomery_ninv) == ~word(0));
		static_assert(sizeof(mint) == sizeof(word));
		
		EEZ_NTT998_ALWAYS_INLINE constexpr word raw(const mint& x) noexcept {
			return x.a;
		}
		
		EEZ_NTT998_ALWAYS_INLINE constexpr mint from_raw(word x) noexcept {
			return mint::montgomery_raw(x);
		}
		
		EEZ_NTT998_ALWAYS_INLINE constexpr word mul(word a, word b) noexcept {
			const u64 x = u64(a) * b;
			const word q = static_cast<word>(x) * montgomery_ninv;
			return static_cast<word>((x + u64(q) * mod) >> 32);
		}
		
		EEZ_NTT998_ALWAYS_INLINE constexpr word add(word a, word b) noexcept {
			const word x = a + b;
			return x >= mod2 ? x - mod2 : x;
		}
		
		EEZ_NTT998_ALWAYS_INLINE constexpr word sub(word a, word b) noexcept {
			return a >= b ? a - b : a + mod2 - b;
		}
		
		EEZ_NTT998_ALWAYS_INLINE constexpr word canonicalize(word a) noexcept {
			return a >= mod ? a - mod : a;
		}
		
		struct twiddle_table{
			std::array<word, max_log + 1> root{};
			std::array<word, max_log + 1> iroot{};
			std::array<word, max_log + 1> rate1{};
			std::array<word, max_log + 1> rate2{};
			std::array<word, max_log + 1> irate2{};
			std::array<word, max_log + 1> rate3{};
			std::array<word, max_log + 1> irate3{};
			
			constexpr twiddle_table(){
				root[max_log] = mint::raw(mint::primitive_root).pow((mod - 1) >> max_log).a;
				iroot[max_log] = mint::montgomery_raw(root[max_log]).inv().a;
				
				for (int i = int(max_log) - 1; i >= 0; --i){
					root[usize(i)] = mul(root[usize(i + 1)], root[usize(i + 1)]);
					iroot[usize(i)] = mul(iroot[usize(i + 1)], iroot[usize(i + 1)]);
				}
				
				word prod = montgomery_one;
				for (unsigned i = 0; i + 1 <= max_log; ++i){
					rate1[i] = mul(root[i + 1], prod);
					prod = mul(prod, iroot[i + 1]);
				}
				
				prod = montgomery_one;
				word iprod = montgomery_one;
				for (unsigned i = 0; i + 2 <= max_log; ++i){
					rate2[i] = mul(root[i + 2], prod);
					irate2[i] = mul(iroot[i + 2], iprod);
					prod = mul(prod, iroot[i + 2]);
					iprod = mul(iprod, root[i + 2]);
				}
				
				prod = montgomery_one;
				iprod = montgomery_one;
				for (unsigned i = 0; i + 3 <= max_log; ++i){
					rate3[i] = mul(root[i + 3], prod);
					irate3[i] = mul(iroot[i + 3], iprod);
					prod = mul(prod, iroot[i + 3]);
					iprod = mul(iprod, root[i + 3]);
				}
			}
		};
		
		inline constexpr twiddle_table twiddles{};
		
		EEZ_NTT998_ALWAYS_INLINE word forward_rate1(unsigned i) noexcept {
			return twiddles.rate1[i];
		}
		
		EEZ_NTT998_ALWAYS_INLINE word forward_rate3(unsigned i) noexcept {
			return twiddles.rate3[i];
		}
		
		EEZ_NTT998_ALWAYS_INLINE word inverse_rate3(unsigned i) noexcept {
			return twiddles.irate3[i];
		}
		
		EEZ_NTT998_ALWAYS_INLINE word forward_rate2(unsigned i) noexcept {
			return twiddles.rate2[i];
		}
		
		EEZ_NTT998_ALWAYS_INLINE word inverse_rate2(unsigned i) noexcept {
			return twiddles.irate2[i];
		}
		
		EEZ_NTT998_ALWAYS_INLINE unsigned twiddle_index(u32 block) noexcept {
			return static_cast<unsigned>(std::countr_zero(~block));
		}
		
#if defined(__AVX2__) || defined(_M_AVX2)
		
		using vec = __m256i;
		
		EEZ_NTT998_ALWAYS_INLINE vec load8(const mint* p) noexcept {
			return _mm256_loadu_si256(reinterpret_cast<const __m256i*>(static_cast<const void*>(p)));
		}
		
		EEZ_NTT998_ALWAYS_INLINE void store8(mint* p, vec x) noexcept {
			_mm256_storeu_si256(reinterpret_cast<__m256i*>(static_cast<void*>(p)), x);
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec broadcast(word x) noexcept {
			return _mm256_set1_epi32(static_cast<int>(x));
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec add8(vec a, vec b) noexcept {
			const vec two_p = broadcast(mod2);
			vec x = _mm256_sub_epi32(_mm256_add_epi32(a, b), two_p);
			return _mm256_add_epi32(x, _mm256_and_si256(_mm256_srai_epi32(x, 31), two_p));
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec sub8(vec a, vec b) noexcept {
			const vec two_p = broadcast(mod2);
			vec x = _mm256_sub_epi32(a, b);
			return _mm256_add_epi32(x, _mm256_and_si256(_mm256_srai_epi32(x, 31), two_p));
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec mul8(vec a, vec b) noexcept {
			const vec ninv = broadcast(montgomery_ninv);
			const vec prime = broadcast(mod);
			
			const vec product_even = _mm256_mul_epu32(a, b);
			const vec product_odd = _mm256_mul_epu32(_mm256_bsrli_epi128(a, 4), _mm256_bsrli_epi128(b, 4));
			
			const vec q_even = _mm256_mul_epu32(product_even, ninv);
			const vec q_odd = _mm256_mul_epu32(product_odd, ninv);
			
			const vec reduced_even = _mm256_add_epi64(product_even, _mm256_mul_epu32(q_even, prime));
			const vec reduced_odd = _mm256_add_epi64(product_odd, _mm256_mul_epu32(q_odd, prime));
			
			return _mm256_or_si256(_mm256_bsrli_epi128(reduced_even, 4), reduced_odd);
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec mul8_fixed(vec a, vec b, vec bninv) noexcept {
			const vec prime = broadcast(mod);
			const vec odd_a = _mm256_bsrli_epi128(a, 4);
			const vec product_even = _mm256_mul_epu32(a, b);
			const vec product_odd = _mm256_mul_epu32(odd_a, b);
			const vec q_even = _mm256_mul_epu32(a, bninv);
			const vec q_odd = _mm256_mul_epu32(odd_a, bninv);
			const vec reduced_even = _mm256_add_epi64(product_even, _mm256_mul_epu32(q_even, prime));
			const vec reduced_odd = _mm256_add_epi64(product_odd, _mm256_mul_epu32(q_odd, prime));
			return _mm256_or_si256(_mm256_bsrli_epi128(reduced_even, 4), reduced_odd);
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec canonicalize8(vec x) noexcept {
			const vec prime = broadcast(mod);
			vec y = _mm256_sub_epi32(x, prime);
			return _mm256_add_epi32(y, _mm256_and_si256(_mm256_srai_epi32(y, 31), prime));
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec pack_four(word x0, word x1) noexcept {
			return _mm256_setr_epi32(
				static_cast<int>(x0), static_cast<int>(x0),
				static_cast<int>(x0), static_cast<int>(x0),
				static_cast<int>(x1), static_cast<int>(x1),
				static_cast<int>(x1), static_cast<int>(x1)
				);
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec load2x4(const mint* p0, const mint* p1) noexcept {
			const __m128i lo = _mm_loadu_si128(reinterpret_cast<const __m128i*>(static_cast<const void*>(p0)));
			const __m128i hi = _mm_loadu_si128(reinterpret_cast<const __m128i*>(static_cast<const void*>(p1)));
			return _mm256_set_m128i(hi, lo);
		}
		
		EEZ_NTT998_ALWAYS_INLINE void store2x4(mint* p0, mint* p1, vec x) noexcept {
			_mm_storeu_si128(reinterpret_cast<__m128i*>(static_cast<void*>(p0)), _mm256_castsi256_si128(x));
			_mm_storeu_si128(reinterpret_cast<__m128i*>(static_cast<void*>(p1)), _mm256_extracti128_si256(x, 1));
		}
		
		EEZ_NTT998_ALWAYS_INLINE void transpose_8x4_to_4x8(
			vec v0,
			vec v1,
			vec v2,
			vec v3,
			vec& x0,
			vec& x1,
			vec& x2,
			vec& x3
			) noexcept {
				const vec t0 = _mm256_unpacklo_epi32(v0, v1);
				const vec t1 = _mm256_unpackhi_epi32(v0, v1);
				const vec t2 = _mm256_unpacklo_epi32(v2, v3);
				const vec t3 = _mm256_unpackhi_epi32(v2, v3);
				const vec perm = _mm256_setr_epi32(0, 4, 1, 5, 2, 6, 3, 7);
				
				x0 = _mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(t0, t2), perm);
				x1 = _mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(t0, t2), perm);
				x2 = _mm256_permutevar8x32_epi32(_mm256_unpacklo_epi64(t1, t3), perm);
				x3 = _mm256_permutevar8x32_epi32(_mm256_unpackhi_epi64(t1, t3), perm);
			}
		
		EEZ_NTT998_ALWAYS_INLINE void transpose_4x8_to_8x4(
			vec x0,
			vec x1,
			vec x2,
			vec x3,
			vec& v0,
			vec& v1,
			vec& v2,
			vec& v3
			) noexcept {
				const vec perm = _mm256_setr_epi32(0, 2, 4, 6, 1, 3, 5, 7);
				const vec q0 = _mm256_permutevar8x32_epi32(x0, perm);
				const vec q1 = _mm256_permutevar8x32_epi32(x1, perm);
				const vec q2 = _mm256_permutevar8x32_epi32(x2, perm);
				const vec q3 = _mm256_permutevar8x32_epi32(x3, perm);
				
				const vec t0 = _mm256_unpacklo_epi64(q0, q1);
				const vec t2 = _mm256_unpackhi_epi64(q0, q1);
				const vec t1 = _mm256_unpacklo_epi64(q2, q3);
				const vec t3 = _mm256_unpackhi_epi64(q2, q3);
				
				v0 = _mm256_castps_si256(_mm256_shuffle_ps(
					_mm256_castsi256_ps(t0),
					_mm256_castsi256_ps(t1),
					_MM_SHUFFLE(2, 0, 2, 0)
					));
				v1 = _mm256_castps_si256(_mm256_shuffle_ps(
					_mm256_castsi256_ps(t0),
					_mm256_castsi256_ps(t1),
					_MM_SHUFFLE(3, 1, 3, 1)
					));
				v2 = _mm256_castps_si256(_mm256_shuffle_ps(
					_mm256_castsi256_ps(t2),
					_mm256_castsi256_ps(t3),
					_MM_SHUFFLE(2, 0, 2, 0)
					));
				v3 = _mm256_castps_si256(_mm256_shuffle_ps(
					_mm256_castsi256_ps(t2),
					_mm256_castsi256_ps(t3),
					_MM_SHUFFLE(3, 1, 3, 1)
					));
			}
		
#endif
		
		EEZ_NTT998_ALWAYS_INLINE void forward_butterfly(mint* b, usize stride, usize i, word r1, word r2, word r3) noexcept {
			const word x0 = raw(b[i]);
			const word x1 = mul(raw(b[stride + i]), r1);
			const word x2 = mul(raw(b[2 * stride + i]), r2);
			const word x3 = mul(raw(b[3 * stride + i]), r3);
			
			const word s02 = add(x0, x2);
			const word d02 = sub(x0, x2);
			const word s13 = add(x1, x3);
			const word t = mul(sub(x1, x3), twiddles.root[2]);
			
			b[i] = from_raw(add(s02, s13));
			b[stride + i] = from_raw(sub(s02, s13));
			b[2 * stride + i] = from_raw(add(d02, t));
			b[3 * stride + i] = from_raw(sub(d02, t));
		}
		
		EEZ_NTT998_ALWAYS_INLINE void inverse_butterfly(mint* b, usize stride, usize i, word r1, word r2, word r3) noexcept {
			const word x0 = raw(b[i]);
			const word x1 = raw(b[stride + i]);
			const word x2 = raw(b[2 * stride + i]);
			const word x3 = raw(b[3 * stride + i]);
			
			const word s01 = add(x0, x1);
			const word d01 = sub(x0, x1);
			const word s23 = add(x2, x3);
			const word t = mul(sub(x2, x3), twiddles.iroot[2]);
			
			b[i] = from_raw(add(s01, s23));
			b[stride + i] = from_raw(mul(add(d01, t), r1));
			b[2 * stride + i] = from_raw(mul(sub(s01, s23), r2));
			b[3 * stride + i] = from_raw(mul(sub(d01, t), r3));
		}
		
		inline void forward_radix4_scalar(mint* EEZ_NTT998_RESTRICT a, usize blocks, usize stride) noexcept {
			{
				mint* const b = a;
				for (usize i = 0; i < stride; ++i) {
					const word x0 = raw(b[i]);
					const word x1 = raw(b[stride + i]);
					const word x2 = raw(b[2 * stride + i]);
					const word x3 = raw(b[3 * stride + i]);
					
					const word s02 = add(x0, x2);
					const word d02 = sub(x0, x2);
					const word s13 = add(x1, x3);
					const word t = mul(sub(x1, x3), twiddles.root[2]);
					
					b[i] = from_raw(add(s02, s13));
					b[stride + i] = from_raw(sub(s02, s13));
					b[2 * stride + i] = from_raw(add(d02, t));
					b[3 * stride + i] = from_raw(sub(d02, t));
				}
			}
			
			if (blocks == 1) return;
			
			word rot = forward_rate3(0);
			
			for (usize s = 1; s < blocks; ++s) {
				const word rot2 = mul(rot, rot);
				const word rot3 = mul(rot2, rot);
				mint* const b = a + s * 4 * stride;
				for (usize i = 0; i < stride; ++i) {
					forward_butterfly(b, stride, i, rot, rot2, rot3);
				}
				if (s + 1 < blocks) {
					rot = mul(
						rot,
						forward_rate3(twiddle_index(static_cast<u32>(s)))
						);
				}
			}
		}
		
		inline void inverse_radix4_scalar(mint* EEZ_NTT998_RESTRICT a, usize blocks, usize stride) noexcept {
			{
				mint* const b = a;
				for (usize i = 0; i < stride; ++i) {
					const word x0 = raw(b[i]);
					const word x1 = raw(b[stride + i]);
					const word x2 = raw(b[2 * stride + i]);
					const word x3 = raw(b[3 * stride + i]);
					
					const word s01 = add(x0, x1);
					const word d01 = sub(x0, x1);
					const word s23 = add(x2, x3);
					const word t = mul(sub(x2, x3), twiddles.iroot[2]);
					
					b[i] = from_raw(add(s01, s23));
					b[stride + i] = from_raw(add(d01, t));
					b[2 * stride + i] = from_raw(sub(s01, s23));
					b[3 * stride + i] = from_raw(sub(d01, t));
				}
			}
			
			if (blocks == 1) return;
			
			word rot = inverse_rate3(0);
			
			for (usize s = 1; s < blocks; ++s) {
				const word rot2 = mul(rot, rot);
				const word rot3 = mul(rot2, rot);
				mint* const b = a + s * 4 * stride;
				for (usize i = 0; i < stride; ++i) {
					inverse_butterfly(b, stride, i, rot, rot2, rot3);
				}
				if (s + 1 < blocks) {
					rot = mul(
						rot,
						inverse_rate3(twiddle_index(static_cast<u32>(s)))
						);
				}
			}
		}
		
#if defined(__AVX2__) || defined(_M_AVX2)
		
		EEZ_NTT998_ALWAYS_INLINE void forward_radix4_large_block(
			mint* EEZ_NTT998_RESTRICT b,
			usize stride,
			vec imag,
			word r1,
			word r2,
			word r3
			) noexcept {
				const vec w1 = broadcast(r1);
				const vec w2 = broadcast(r2);
				const vec w3 = broadcast(r3);
				
				for (usize i = 0; i < stride; i += 8){
					const vec x0 = load8(b + i);
					const vec x1 = mul8(load8(b + stride + i), w1);
					const vec x2 = mul8(load8(b + 2 * stride + i), w2);
					const vec x3 = mul8(load8(b + 3 * stride + i), w3);
					
					const vec s02 = add8(x0, x2);
					const vec d02 = sub8(x0, x2);
					const vec s13 = add8(x1, x3);
					const vec t = mul8(sub8(x1, x3), imag);
					
					store8(b + i, add8(s02, s13));
					store8(b + stride + i, sub8(s02, s13));
					store8(b + 2 * stride + i, add8(d02, t));
					store8(b + 3 * stride + i, sub8(d02, t));
				}
			}
		
		EEZ_NTT998_ALWAYS_INLINE void inverse_radix4_large_block(
			mint* EEZ_NTT998_RESTRICT b,
			usize stride,
			vec iimag,
			word r1,
			word r2,
			word r3
			) noexcept {
				const vec w1 = broadcast(r1);
				const vec w2 = broadcast(r2);
				const vec w3 = broadcast(r3);
				
				for (usize i = 0; i < stride; i += 8){
					const vec x0 = load8(b + i);
					const vec x1 = load8(b + stride + i);
					const vec x2 = load8(b + 2 * stride + i);
					const vec x3 = load8(b + 3 * stride + i);
					
					const vec s01 = add8(x0, x1);
					const vec d01 = sub8(x0, x1);
					const vec s23 = add8(x2, x3);
					const vec t = mul8(sub8(x2, x3), iimag);
					
					store8(b + i, add8(s01, s23));
					store8(b + stride + i, mul8(add8(d01, t), w1));
					store8(b + 2 * stride + i, mul8(sub8(s01, s23), w2));
					store8(b + 3 * stride + i, mul8(sub8(d01, t), w3));
				}
			}
		
		inline void forward_radix4_large(mint* EEZ_NTT998_RESTRICT a, usize blocks, usize stride) noexcept {
			const vec imag = broadcast(twiddles.root[2]);
			{
				mint* const b = a;
				for (usize i = 0; i < stride; i += 8){
					const vec x0 = load8(b + i);
					const vec x1 = load8(b + stride + i);
					const vec x2 = load8(b + 2 * stride + i);
					const vec x3 = load8(b + 3 * stride + i);
					
					const vec s02 = add8(x0, x2);
					const vec d02 = sub8(x0, x2);
					const vec s13 = add8(x1, x3);
					const vec t = mul8(sub8(x1, x3), imag);
					
					store8(b + i, add8(s02, s13));
					store8(b + stride + i, sub8(s02, s13));
					store8(b + 2 * stride + i, add8(d02, t));
					store8(b + 3 * stride + i, sub8(d02, t));
				}
			}
			
			if (blocks == 1) return;
			
			word rot = forward_rate3(0);
			usize s = 1;
			
			for (; s + 8 <= blocks; s += 8){
				alignas(32) word r1[8];
				alignas(32) word r2[8];
				alignas(32) word r3[8];
				for (unsigned lane = 0; lane < 8; ++lane){
					r1[lane] = rot;
					if (s + lane + 1 < blocks){
						rot = mul(rot, forward_rate3(twiddle_index(static_cast<u32>(s + lane))));
					}
				}
				
				const vec w1 = _mm256_load_si256(reinterpret_cast<const vec*>(r1));
				const vec w2 = mul8(w1, w1);
				const vec w3 = mul8(w2, w1);
				_mm256_store_si256(reinterpret_cast<vec*>(r2), w2);
				_mm256_store_si256(reinterpret_cast<vec*>(r3), w3);
				
				for (unsigned lane = 0; lane < 8; ++lane){
					forward_radix4_large_block(
						a + (s + lane) * 4 * stride,
						stride,
						imag,
						r1[lane],
						r2[lane],
						r3[lane]
						);
				}
			}
			
			for (; s < blocks; ++s){
				const word rot2 = mul(rot, rot);
				const word rot3 = mul(rot2, rot);
				forward_radix4_large_block(a + s * 4 * stride, stride, imag, rot, rot2, rot3);
				
				if (s + 1 < blocks){
					rot = mul(rot, forward_rate3(twiddle_index(static_cast<u32>(s))));
				}
			}
		}
		
		inline void inverse_radix4_large(mint* EEZ_NTT998_RESTRICT a, usize blocks, usize stride) noexcept {
			const vec iimag = broadcast(twiddles.iroot[2]);
			{
				mint* const b = a;
				for (usize i = 0; i < stride; i += 8){
					const vec x0 = load8(b + i);
					const vec x1 = load8(b + stride + i);
					const vec x2 = load8(b + 2 * stride + i);
					const vec x3 = load8(b + 3 * stride + i);
					
					const vec s01 = add8(x0, x1);
					const vec d01 = sub8(x0, x1);
					const vec s23 = add8(x2, x3);
					const vec t = mul8(sub8(x2, x3), iimag);
					
					store8(b + i, add8(s01, s23));
					store8(b + stride + i, add8(d01, t));
					store8(b + 2 * stride + i, sub8(s01, s23));
					store8(b + 3 * stride + i, sub8(d01, t));
				}
			}
			
			if (blocks == 1) return;
			
			word rot = inverse_rate3(0);
			usize s = 1;
			
			for (; s + 8 <= blocks; s += 8){
				alignas(32) word r1[8];
				alignas(32) word r2[8];
				alignas(32) word r3[8];
				for (unsigned lane = 0; lane < 8; ++lane){
					r1[lane] = rot;
					if (s + lane + 1 < blocks){
						rot = mul(rot, inverse_rate3(twiddle_index(static_cast<u32>(s + lane))));
					}
				}
				
				const vec w1 = _mm256_load_si256(reinterpret_cast<const vec*>(r1));
				const vec w2 = mul8(w1, w1);
				const vec w3 = mul8(w2, w1);
				_mm256_store_si256(reinterpret_cast<vec*>(r2), w2);
				_mm256_store_si256(reinterpret_cast<vec*>(r3), w3);
				
				for (unsigned lane = 0; lane < 8; ++lane){
					inverse_radix4_large_block(
						a + (s + lane) * 4 * stride,
						stride,
						iimag,
						r1[lane],
						r2[lane],
						r3[lane]
						);
				}
			}
			
			for (; s < blocks; ++s){
				const word rot2 = mul(rot, rot);
				const word rot3 = mul(rot2, rot);
				inverse_radix4_large_block(a + s * 4 * stride, stride, iimag, rot, rot2, rot3);
				
				if (s + 1 < blocks){
					rot = mul(rot, inverse_rate3(twiddle_index(static_cast<u32>(s))));
				}
			}
		}
		
		inline void forward_radix4_p4(mint* EEZ_NTT998_RESTRICT a, usize blocks) noexcept {
			if (blocks < 2){
				forward_radix4_scalar(a, blocks, 4);
				return;
			}
			
			const vec imag = broadcast(twiddles.root[2]);
			word rot = montgomery_one;
			
			for (usize s = 0; s < blocks; s += 2){
				const word r10 = rot;
				rot = mul(rot, forward_rate3(twiddle_index(static_cast<u32>(s))));
				const word r11 = rot;
				
				const vec w1 = pack_four(r10, r11);
				const vec w2 = mul8(w1, w1);
				const vec w3 = mul8(w2, w1);
				mint* const b0 = a + s * 16;
				mint* const b1 = b0 + 16;
				
				const vec x0 = load2x4(b0, b1);
				const vec x1 = mul8(load2x4(b0 + 4, b1 + 4), w1);
				const vec x2 = mul8(load2x4(b0 + 8, b1 + 8), w2);
				const vec x3 = mul8(load2x4(b0 + 12, b1 + 12), w3);
				
				const vec s02 = add8(x0, x2);
				const vec d02 = sub8(x0, x2);
				const vec s13 = add8(x1, x3);
				const vec t = mul8(sub8(x1, x3), imag);
				
				store2x4(b0, b1, add8(s02, s13));
				store2x4(b0 + 4, b1 + 4, sub8(s02, s13));
				store2x4(b0 + 8, b1 + 8, add8(d02, t));
				store2x4(b0 + 12, b1 + 12, sub8(d02, t));
				
				if (s + 2 < blocks){
					rot = mul(rot, forward_rate3(twiddle_index(static_cast<u32>(s + 1))));
				}
			}
		}
		
		inline void inverse_radix4_p4(mint* EEZ_NTT998_RESTRICT a, usize blocks) noexcept {
			if (blocks < 2){
				inverse_radix4_scalar(a, blocks, 4);
				return;
			}
			
			const vec iimag = broadcast(twiddles.iroot[2]);
			word rot = montgomery_one;
			
			for (usize s = 0; s < blocks; s += 2){
				const word r10 = rot;
				rot = mul(rot, inverse_rate3(twiddle_index(static_cast<u32>(s))));
				const word r11 = rot;
				
				const vec w1 = pack_four(r10, r11);
				const vec w2 = mul8(w1, w1);
				const vec w3 = mul8(w2, w1);
				mint* const b0 = a + s * 16;
				mint* const b1 = b0 + 16;
				
				const vec x0 = load2x4(b0, b1);
				const vec x1 = load2x4(b0 + 4, b1 + 4);
				const vec x2 = load2x4(b0 + 8, b1 + 8);
				const vec x3 = load2x4(b0 + 12, b1 + 12);
				
				const vec s01 = add8(x0, x1);
				const vec d01 = sub8(x0, x1);
				const vec s23 = add8(x2, x3);
				const vec t = mul8(sub8(x2, x3), iimag);
				
				store2x4(b0, b1, add8(s01, s23));
				store2x4(b0 + 4, b1 + 4, mul8(add8(d01, t), w1));
				store2x4(b0 + 8, b1 + 8, mul8(sub8(s01, s23), w2));
				store2x4(b0 + 12, b1 + 12, mul8(sub8(d01, t), w3));
				
				if (s + 2 < blocks){
					rot = mul(rot, inverse_rate3(twiddle_index(static_cast<u32>(s + 1))));
				}
			}
		}
		
		inline void forward_radix4_p1(mint* EEZ_NTT998_RESTRICT a, usize blocks) noexcept {
			const vec imag = broadcast(twiddles.root[2]);
			word rot = montgomery_one;
			usize s = 0;
			
			for (; s + 8 <= blocks; s += 8){
				alignas(32) word r1[8];
				for (unsigned lane = 0; lane < 8; ++lane){
					r1[lane] = rot;
					if (s + lane + 1 < blocks){
						rot = mul(rot, forward_rate3(twiddle_index(static_cast<u32>(s + lane))));
					}
				}
				
				const vec w1 = _mm256_load_si256(reinterpret_cast<const vec*>(r1));
				const vec w2 = mul8(w1, w1);
				const vec w3 = mul8(w2, w1);
				
				mint* const b = a + 4 * s;
				vec x0;
				vec x1;
				vec x2;
				vec x3;
				transpose_8x4_to_4x8(load8(b), load8(b + 8), load8(b + 16), load8(b + 24), x0, x1, x2, x3);
				
				x1 = mul8(x1, w1);
				x2 = mul8(x2, w2);
				x3 = mul8(x3, w3);
				
				const vec s02 = add8(x0, x2);
				const vec d02 = sub8(x0, x2);
				const vec s13 = add8(x1, x3);
				const vec t = mul8(sub8(x1, x3), imag);
				
				vec v0;
				vec v1;
				vec v2;
				vec v3;
				transpose_4x8_to_8x4(add8(s02, s13), sub8(s02, s13), add8(d02, t), sub8(d02, t), v0, v1, v2, v3);
				store8(b, v0);
				store8(b + 8, v1);
				store8(b + 16, v2);
				store8(b + 24, v3);
			}
			
			for (; s < blocks; ++s){
				const word rot2 = mul(rot, rot);
				const word rot3 = mul(rot2, rot);
				forward_butterfly(a + 4 * s, 1, 0, rot, rot2, rot3);
				if (s + 1 < blocks){
					rot = mul(rot, forward_rate3(twiddle_index(static_cast<u32>(s))));
				}
			}
		}
		
		inline void inverse_radix4_p1(mint* EEZ_NTT998_RESTRICT a, usize blocks) noexcept {
			const vec iimag = broadcast(twiddles.iroot[2]);
			word rot = montgomery_one;
			usize s = 0;
			
			for (; s + 8 <= blocks; s += 8){
				alignas(32) word r1[8];
				for (unsigned lane = 0; lane < 8; ++lane){
					r1[lane] = rot;
					if (s + lane + 1 < blocks){
						rot = mul(rot, inverse_rate3(twiddle_index(static_cast<u32>(s + lane))));
					}
				}
				
				const vec w1 = _mm256_load_si256(reinterpret_cast<const vec*>(r1));
				const vec w2 = mul8(w1, w1);
				const vec w3 = mul8(w2, w1);
				
				mint* const b = a + 4 * s;
				vec x0;
				vec x1;
				vec x2;
				vec x3;
				transpose_8x4_to_4x8(load8(b), load8(b + 8), load8(b + 16), load8(b + 24), x0, x1, x2, x3);
				
				const vec s01 = add8(x0, x1);
				const vec d01 = sub8(x0, x1);
				const vec s23 = add8(x2, x3);
				const vec t = mul8(sub8(x2, x3), iimag);
				
				vec v0;
				vec v1;
				vec v2;
				vec v3;
				transpose_4x8_to_8x4(
					add8(s01, s23),
					mul8(add8(d01, t), w1),
					mul8(sub8(s01, s23), w2),
					mul8(sub8(d01, t), w3),
					v0,
					v1,
					v2,
					v3
					);
				store8(b, v0);
				store8(b + 8, v1);
				store8(b + 16, v2);
				store8(b + 24, v3);
			}
			
			for (; s < blocks; ++s){
				const word rot2 = mul(rot, rot);
				const word rot3 = mul(rot2, rot);
				inverse_butterfly(a + 4 * s, 1, 0, rot, rot2, rot3);
				if (s + 1 < blocks){
					rot = mul(rot, inverse_rate3(twiddle_index(static_cast<u32>(s))));
				}
			}
		}
		
#endif
		
		inline void forward_radix2_first(mint* EEZ_NTT998_RESTRICT a, usize n) noexcept {
			const usize half = n >> 1;
			usize i = 0;
			
#if defined(__AVX2__) || defined(_M_AVX2)
			for (; i + 8 <= half; i += 8){
				const vec x = load8(a + i);
				const vec y = load8(a + half + i);
				store8(a + i, add8(x, y));
				store8(a + half + i, sub8(x, y));
			}
#endif
			
			for (; i < half; ++i){
				const word x = raw(a[i]);
				const word y = raw(a[half + i]);
				a[i] = from_raw(add(x, y));
				a[half + i] = from_raw(sub(x, y));
			}
		}
		
		inline void forward_radix4_stage(mint* EEZ_NTT998_RESTRICT a, usize n, int stage) noexcept {
			const int h = static_cast<int>(std::countr_zero(n));
			assert(stage >= 0 && stage + 2 <= h);
			const usize stride = usize(1) << (h - stage - 2);
			const usize blocks = usize(1) << stage;
			
#if defined(__AVX2__) || defined(_M_AVX2)
			if (stride >= 8){
				forward_radix4_large(a, blocks, stride);
			} else if (stride == 4){
				forward_radix4_p4(a, blocks);
			} else if (stride == 1){
				forward_radix4_p1(a, blocks);
			} else{
				forward_radix4_scalar(a, blocks, stride);
			}
#else
			forward_radix4_scalar(a, blocks, stride);
#endif
		}
		
		inline void inverse_radix4_stage(mint* EEZ_NTT998_RESTRICT a, usize n, int stage) noexcept {
			const int h = static_cast<int>(std::countr_zero(n));
			assert(stage >= 0 && stage + 2 <= h);
			const usize stride = usize(1) << (h - stage - 2);
			const usize blocks = usize(1) << stage;
			
#if defined(__AVX2__) || defined(_M_AVX2)
			if (stride >= 8){
				inverse_radix4_large(a, blocks, stride);
			} else if (stride == 4){
				inverse_radix4_p4(a, blocks);
			} else if (stride == 1){
				inverse_radix4_p1(a, blocks);
			} else{
				inverse_radix4_scalar(a, blocks, stride);
			}
#else
			inverse_radix4_scalar(a, blocks, stride);
#endif
		}
		
		inline void final_radix2_scale(mint* EEZ_NTT998_RESTRICT a, usize n, word scale_mont) noexcept {
			const usize half = n >> 1;
			usize i = 0;
			
#if defined(__AVX2__) || defined(_M_AVX2)
			const vec scale = broadcast(scale_mont);
			for (; i + 8 <= half; i += 8){
				const vec x = load8(a + i);
				const vec y = load8(a + half + i);
				store8(a + i, mul8(add8(x, y), scale));
				store8(a + half + i, mul8(sub8(x, y), scale));
			}
#endif
			
			for (; i < half; ++i){
				const word x = raw(a[i]);
				const word y = raw(a[half + i]);
				a[i] = from_raw(mul(add(x, y), scale_mont));
				a[half + i] = from_raw(mul(sub(x, y), scale_mont));
			}
		}
		
		inline void inverse_radix2_final(mint* EEZ_NTT998_RESTRICT a, usize n, word scale) noexcept {
			final_radix2_scale(a, n, scale);
		}
		
		inline void final_radix4_scale(mint* EEZ_NTT998_RESTRICT a, usize n, word scale_mont) noexcept {
			const usize stride = n >> 2;
			usize i = 0;
			
#if defined(__AVX2__) || defined(_M_AVX2)
			const vec iimag = broadcast(twiddles.iroot[2]);
			const vec scale = broadcast(scale_mont);
			for (; i + 8 <= stride; i += 8){
				const vec x0 = load8(a + i);
				const vec x1 = load8(a + stride + i);
				const vec x2 = load8(a + 2 * stride + i);
				const vec x3 = load8(a + 3 * stride + i);
				
				const vec s01 = add8(x0, x1);
				const vec d01 = sub8(x0, x1);
				const vec s23 = add8(x2, x3);
				const vec t = mul8(sub8(x2, x3), iimag);
				
				store8(a + i, mul8(add8(s01, s23), scale));
				store8(a + stride + i, mul8(add8(d01, t), scale));
				store8(a + 2 * stride + i, mul8(sub8(s01, s23), scale));
				store8(a + 3 * stride + i, mul8(sub8(d01, t), scale));
			}
#endif
			
			for (; i < stride; ++i){
				const word x0 = raw(a[i]);
				const word x1 = raw(a[stride + i]);
				const word x2 = raw(a[2 * stride + i]);
				const word x3 = raw(a[3 * stride + i]);
				const word s01 = add(x0, x1);
				const word d01 = sub(x0, x1);
				const word s23 = add(x2, x3);
				const word t = mul(sub(x2, x3), twiddles.iroot[2]);
				
				a[i] = from_raw(mul(add(s01, s23), scale_mont));
				a[stride + i] = from_raw(mul(add(d01, t), scale_mont));
				a[2 * stride + i] = from_raw(mul(sub(s01, s23), scale_mont));
				a[3 * stride + i] = from_raw(mul(sub(d01, t), scale_mont));
			}
		}
		
		inline void forward_dif(mint* EEZ_NTT998_RESTRICT a, usize n) noexcept {
			if (n <= 1) return;
			const int h = static_cast<int>(std::countr_zero(n));
			int stage = 0;
			
			if (h & 1){
				forward_radix2_first(a, n);
				stage = 1;
			}
			
			for (; stage < h; stage += 2){
				forward_radix4_stage(a, n, stage);
			}
		}
		
		inline void inverse_dit(mint* EEZ_NTT998_RESTRICT a, usize n) noexcept {
			if (n <= 1) return;
			const int h = static_cast<int>(std::countr_zero(n));
			const word scale = mint::raw(static_cast<u32>(n)).inv().a;
			
			if (h & 1){
				for (int stage = h - 2; stage >= 1; stage -= 2){
					inverse_radix4_stage(a, n, stage);
				}
				final_radix2_scale(a, n, scale);
			} else{
				for (int stage = h - 2; stage >= 2; stage -= 2){
					inverse_radix4_stage(a, n, stage);
				}
				final_radix4_scale(a, n, scale);
			}
		}
		
		inline void forward_dif_partial(mint* EEZ_NTT998_RESTRICT a, usize n) noexcept {
			if (n <= 4) return;
			const int h = static_cast<int>(std::countr_zero(n));
			const int levels = h - 2;
			int stage = 0;
			
			if (levels & 1){
				forward_radix2_first(a, n);
				stage = 1;
			}
			
			for (; stage < levels; stage += 2){
				forward_radix4_stage(a, n, stage);
			}
		}
		
		inline void inverse_dit_partial(mint* EEZ_NTT998_RESTRICT a, usize n) noexcept {
			if (n <= 4) return;
			const int h = static_cast<int>(std::countr_zero(n));
			const int levels = h - 2;
			const word scale = mint::raw(static_cast<u32>(n >> 2)).inv().a;
			
			if (levels & 1){
				for (int stage = levels - 2; stage >= 1; stage -= 2){
					inverse_radix4_stage(a, n, stage);
				}
				final_radix2_scale(a, n, scale);
			} else{
				for (int stage = levels - 2; stage >= 2; stage -= 2){
					inverse_radix4_stage(a, n, stage);
				}
				final_radix4_scale(a, n, scale);
			}
		}
		
		EEZ_NTT998_ALWAYS_INLINE word block_modulus4(word w, u32 block) noexcept {
			return mul(w, forward_rate1(twiddle_index(block)));
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec block_product4x2(vec x, vec y, vec w) noexcept {
			const vec z = _mm256_setzero_si256();
			vec lo = mul8(_mm256_shuffle_epi32(x, _MM_SHUFFLE(0, 0, 0, 0)), y);
			vec hi = z;
			
			{
				const vec p = mul8(_mm256_shuffle_epi32(x, _MM_SHUFFLE(1, 1, 1, 1)), y);
				const vec q = _mm256_shuffle_epi32(p, _MM_SHUFFLE(2, 1, 0, 3));
				lo = add8(lo, _mm256_blend_epi32(q, z, 0x11));
				hi = add8(hi, _mm256_blend_epi32(z, q, 0x11));
			}
			{
				const vec p = mul8(_mm256_shuffle_epi32(x, _MM_SHUFFLE(2, 2, 2, 2)), y);
				const vec q = _mm256_shuffle_epi32(p, _MM_SHUFFLE(1, 0, 3, 2));
				lo = add8(lo, _mm256_blend_epi32(q, z, 0x33));
				hi = add8(hi, _mm256_blend_epi32(z, q, 0x33));
			}
			{
				const vec p = mul8(_mm256_shuffle_epi32(x, _MM_SHUFFLE(3, 3, 3, 3)), y);
				const vec q = _mm256_shuffle_epi32(p, _MM_SHUFFLE(0, 3, 2, 1));
				lo = add8(lo, _mm256_blend_epi32(q, z, 0x77));
				hi = add8(hi, _mm256_blend_epi32(z, q, 0x77));
			}
			
			return add8(lo, mul8(hi, w));
		}
		
		inline void block_product4_scalar(mint* a, const mint* b, word w) noexcept {
			word x[4];
			word y[4];
			word result[4]{};
			for (unsigned i = 0; i < 4; ++i){
				x[i] = raw(a[i]);
				y[i] = raw(b[i]);
			}
			for (unsigned i = 0; i < 4; ++i){
				for (unsigned j = 0; j < 4; ++j){
					const unsigned degree = i + j;
					word term = mul(x[i], y[j]);
					if (degree >= 4) term = mul(term, w);
					result[degree & 3] = add(result[degree & 3], term);
				}
			}
			for (unsigned i = 0; i < 4; ++i) a[i] = from_raw(result[i]);
		}
		
		inline void block_convolution4(mint* EEZ_NTT998_RESTRICT a, const mint* EEZ_NTT998_RESTRICT b, usize n) noexcept {
			const usize blocks = n >> 2;
			word w = montgomery_one;
			usize s = 0;
			
			for (; s + 2 <= blocks; s += 2){
				const word w1 = block_modulus4(w, static_cast<u32>(s));
				const vec modulus = pack_four(w, w1);
				store8(a + 4 * s, block_product4x2(load8(a + 4 * s), load8(b + 4 * s), modulus));
				if (s + 2 < blocks){
					w = block_modulus4(w1, static_cast<u32>(s + 1));
				}
			}
			if (s < blocks) block_product4_scalar(a + 4 * s, b + 4 * s, w);
		}
		
		inline void block_square4(mint* EEZ_NTT998_RESTRICT a, usize n) noexcept {
			const usize blocks = n >> 2;
			word w = montgomery_one;
			usize s = 0;
			
			for (; s + 2 <= blocks; s += 2){
				const word w1 = block_modulus4(w, static_cast<u32>(s));
				const vec x = load8(a + 4 * s);
				store8(a + 4 * s, block_product4x2(x, x, pack_four(w, w1)));
				if (s + 2 < blocks){
					w = block_modulus4(w1, static_cast<u32>(s + 1));
				}
			}
			if (s < blocks) block_product4_scalar(a + 4 * s, a + 4 * s, w);
		}
		
#if defined(__AVX2__) || defined(_M_AVX2)
		
		class aligned_buffer {
			mint* data_ = nullptr;
			usize size_ = 0;
			
		public:
			explicit aligned_buffer(usize n)
			: data_(static_cast<mint*>(::operator new[](n * sizeof(mint), std::align_val_t{64}))),
			size_(n) {
				std::uninitialized_value_construct_n(data_, size_);
			}
			
			aligned_buffer(const aligned_buffer&) = delete;
			aligned_buffer& operator=(const aligned_buffer&) = delete;
			
			~aligned_buffer() {
				std::destroy_n(data_, size_);
				::operator delete[](data_, std::align_val_t{64});
			}
			
			mint* data() noexcept { return data_; }
			const mint* data() const noexcept { return data_; }
			mint& operator[](usize i) noexcept { return data_[i]; }
			const mint& operator[](usize i) const noexcept { return data_[i]; }
		};
		
		class aligned_uninitialized_buffer {
			static_assert(std::is_trivially_destructible_v<mint>);
			mint* data_ = nullptr;
			
		public:
			explicit aligned_uninitialized_buffer(usize n)
			: data_(static_cast<mint*>(::operator new[](n * sizeof(mint), std::align_val_t{64}))) {}
			
			aligned_uninitialized_buffer(const aligned_uninitialized_buffer&) = delete;
			aligned_uninitialized_buffer& operator=(const aligned_uninitialized_buffer&) = delete;
			
			~aligned_uninitialized_buffer() {
				::operator delete[](data_, std::align_val_t{64});
			}
			
			mint* data() noexcept { return data_; }
			const mint* data() const noexcept { return data_; }
		};
		
		EEZ_NTT998_ALWAYS_INLINE vec load8_aligned(const mint* p) noexcept {
			return _mm256_load_si256(reinterpret_cast<const __m256i*>(static_cast<const void*>(p)));
		}
		
		EEZ_NTT998_ALWAYS_INLINE void store8_aligned(mint* p, vec x) noexcept {
			_mm256_store_si256(reinterpret_cast<__m256i*>(static_cast<void*>(p)), x);
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec shrink4_to_2(vec x) noexcept {
			return _mm256_min_epu32(x, _mm256_sub_epi32(x, broadcast(mod2)));
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec lazy_add8(vec a, vec b) noexcept {
			return _mm256_add_epi32(a, b);
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec lazy_sub8(vec a, vec b) noexcept {
			return _mm256_add_epi32(a, _mm256_sub_epi32(broadcast(mod2), b));
		}
		
		template <bool trivial_twiddle, bool convert_input = false>
		inline void forward_radix4_block_lazy(mint* b, usize stride, word r1) noexcept {
			const word imag = canonicalize(twiddles.root[2]);
			const vec vimag = broadcast(imag);
			const vec vimag_ninv = broadcast(imag * montgomery_ninv);
			const vec vr1 = broadcast(r1);
			const vec vr1_ninv = broadcast(r1 * montgomery_ninv);
			const word r2 = canonicalize(mul(r1, r1));
			const vec vr2 = broadcast(r2);
			const vec vr2_ninv = broadcast(r2 * montgomery_ninv);
			const word r3 = canonicalize(mul(r2, r1));
			const vec vr3 = broadcast(r3);
			const vec vr3_ninv = broadcast(r3 * montgomery_ninv);
			
			for(usize i = 0; i < stride; i += 8){
				vec x0 = shrink4_to_2(load8_aligned(b + i));
				vec x1 = load8_aligned(b + stride + i);
				vec x2 = load8_aligned(b + 2 * stride + i);
				vec x3 = load8_aligned(b + 3 * stride + i);
				if constexpr(!trivial_twiddle){
					x1 = mul8_fixed(x1, vr1, vr1_ninv);
					x2 = mul8_fixed(x2, vr2, vr2_ninv);
					x3 = mul8_fixed(x3, vr3, vr3_ninv);
				}else{
					x1 = shrink4_to_2(x1);
					x2 = shrink4_to_2(x2);
					x3 = shrink4_to_2(x3);
				}
				
				vec s02 = lazy_add8(x0, x2);
				vec d02 = lazy_sub8(x0, x2);
				vec s13 = lazy_add8(x1, x3);
				const vec t = mul8_fixed(lazy_sub8(x1, x3), vimag, vimag_ninv);
				s02 = shrink4_to_2(s02);
				d02 = shrink4_to_2(d02);
				s13 = shrink4_to_2(s13);
				
				vec y0 = lazy_add8(s02, s13);
				vec y1 = lazy_sub8(s02, s13);
				vec y2 = lazy_add8(d02, t);
				vec y3 = lazy_sub8(d02, t);
				if constexpr(convert_input){
					constexpr word montgomery_r2 = 932051910u;
					const vec vr2_convert = broadcast(montgomery_r2);
					const vec vr2_convert_ninv = broadcast(montgomery_r2 * montgomery_ninv);
					y0 = mul8_fixed(y0, vr2_convert, vr2_convert_ninv);
					y1 = mul8_fixed(y1, vr2_convert, vr2_convert_ninv);
					y2 = mul8_fixed(y2, vr2_convert, vr2_convert_ninv);
					y3 = mul8_fixed(y3, vr2_convert, vr2_convert_ninv);
				}
				
				store8_aligned(b + i,              y0);
				store8_aligned(b + stride + i,     y1);
				store8_aligned(b + 2 * stride + i, y2);
				store8_aligned(b + 3 * stride + i, y3);
			}
		}
		
		template <bool trivial_twiddle, bool convert_input = false>
		EEZ_NTT998_ALWAYS_INLINE void forward_radix4_block_pair_lazy(mint* EEZ_NTT998_RESTRICT a, mint* EEZ_NTT998_RESTRICT b, usize stride, word r1) noexcept {
			forward_radix4_block_lazy<trivial_twiddle, convert_input>(a, stride, r1);
			forward_radix4_block_lazy<trivial_twiddle, convert_input>(b, stride, r1);
		}
		
		template <bool trivial_twiddle, bool apply_scale, bool convert_output = false, bool direct_output = false>
		inline void inverse_radix4_block_lazy(mint* b, usize stride, word r1, word scale) noexcept {
			const word iimag = canonicalize(twiddles.iroot[2]);
			const vec viimag = broadcast(iimag);
			const vec viimag_ninv = broadcast(iimag * montgomery_ninv);
			const vec vr1 = broadcast(r1);
			const vec vr1_ninv = broadcast(r1 * montgomery_ninv);
			const word r2 = canonicalize(mul(r1, r1));
			const vec vr2 = broadcast(r2);
			const vec vr2_ninv = broadcast(r2 * montgomery_ninv);
			const word r3 = canonicalize(mul(r2, r1));
			const vec vr3 = broadcast(r3);
			const vec vr3_ninv = broadcast(r3 * montgomery_ninv);
			const word scale_canonical = canonicalize(scale);
			
			for(usize i = 0; i < stride; i += 8){
				const vec x0 = shrink4_to_2(load8_aligned(b + i));
				const vec x1 = shrink4_to_2(load8_aligned(b + stride + i));
				const vec x2 = shrink4_to_2(load8_aligned(b + 2 * stride + i));
				const vec x3 = shrink4_to_2(load8_aligned(b + 3 * stride + i));
				
				vec s01 = lazy_add8(x0, x1);
				vec d01 = lazy_sub8(x0, x1);
				vec s23 = lazy_add8(x2, x3);
				const vec t = mul8_fixed(lazy_sub8(x2, x3), viimag, viimag_ninv);
				s01 = shrink4_to_2(s01);
				d01 = shrink4_to_2(d01);
				s23 = shrink4_to_2(s23);
				
				vec y0 = lazy_add8(s01, s23);
				vec y1 = lazy_add8(d01, t);
				vec y2 = lazy_sub8(s01, s23);
				vec y3 = lazy_sub8(d01, t);
				if constexpr(apply_scale){
					const word s0 = scale_canonical;
					const word s1 = trivial_twiddle ? s0 : canonicalize(mul(s0, r1));
					const word s2 = trivial_twiddle ? s0 : canonicalize(mul(s0, r2));
					const word s3 = trivial_twiddle ? s0 : canonicalize(mul(s0, r3));
					const vec vs0 = broadcast(s0);
					const vec vs1 = broadcast(s1);
					const vec vs2 = broadcast(s2);
					const vec vs3 = broadcast(s3);
					y0 = mul8_fixed(y0, vs0, broadcast(s0 * montgomery_ninv));
					y1 = mul8_fixed(y1, vs1, broadcast(s1 * montgomery_ninv));
					y2 = mul8_fixed(y2, vs2, broadcast(s2 * montgomery_ninv));
					y3 = mul8_fixed(y3, vs3, broadcast(s3 * montgomery_ninv));
				}else if constexpr(!trivial_twiddle){
					y1 = mul8_fixed(y1, vr1, vr1_ninv);
					y2 = mul8_fixed(y2, vr2, vr2_ninv);
					y3 = mul8_fixed(y3, vr3, vr3_ninv);
				}
				if constexpr(convert_output){
					const vec vone = broadcast(1);
					const vec vninv = broadcast(montgomery_ninv);
					y0 = canonicalize8(mul8_fixed(y0, vone, vninv));
					y1 = canonicalize8(mul8_fixed(y1, vone, vninv));
					y2 = canonicalize8(mul8_fixed(y2, vone, vninv));
					y3 = canonicalize8(mul8_fixed(y3, vone, vninv));
				}else if constexpr(direct_output){
					y0 = canonicalize8(shrink4_to_2(y0));
					y1 = canonicalize8(shrink4_to_2(y1));
					y2 = canonicalize8(shrink4_to_2(y2));
					y3 = canonicalize8(shrink4_to_2(y3));
				}
				
				store8_aligned(b + i,              y0);
				store8_aligned(b + stride + i,     y1);
				store8_aligned(b + 2 * stride + i, y2);
				store8_aligned(b + 3 * stride + i, y3);
			}
		}
		
		inline unsigned adaptive_leaf_log(usize n) noexcept {
			const unsigned h = static_cast<unsigned>(std::countr_zero(n));
			return (h & 1u) ? 3u : 4u;
		}
		
		template <bool convert_input = false>
		EEZ_NTT998_ALWAYS_INLINE void forward_cache_node(mint* EEZ_NTT998_RESTRICT base, usize block_size, unsigned layer, usize block, usize blocks_at_layer, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			const usize stride = block_size >> 2;
			if constexpr(convert_input) forward_radix4_block_lazy<true, true>(base, stride, montgomery_one);
			else if(block == 0) forward_radix4_block_lazy<true>(base, stride, montgomery_one);
			else forward_radix4_block_lazy<false>(base, stride, rotation[layer]);
			if(block + 1 < blocks_at_layer) rotation[layer] = canonicalize(mul(rotation[layer], forward_rate3(twiddle_index(static_cast<u32>(block)))));
		}
		
		template <bool convert_input = false>
		inline void forward_cache_block(mint* EEZ_NTT998_RESTRICT base, usize block_size, unsigned layer, usize block, usize blocks_at_layer, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			forward_cache_node<convert_input>(base, block_size, layer, block, blocks_at_layer, rotation);
			const usize child_size = block_size >> 2;
			for(usize child = 0; child < 4; ++child){
				mint* const child_base = base + child * child_size;
				const usize child_block = block * 4 + child;
				forward_cache_node(child_base, child_size, layer + 1, child_block, blocks_at_layer * 4, rotation);
				const usize grandchild_size = child_size >> 2;
				for(usize grandchild = 0; grandchild < 4; ++grandchild){
					forward_cache_node(child_base + grandchild * grandchild_size, grandchild_size, layer + 2, child_block * 4 + grandchild, blocks_at_layer * 16, rotation);
				}
			}
		}
		
		template <bool convert_input = false>
		inline void forward_cache_dfs(mint* EEZ_NTT998_RESTRICT base, usize block_size, usize leaf_size, unsigned layer, usize block, usize blocks_at_layer, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			if(block_size == leaf_size * 64){
				forward_cache_block<convert_input>(base, block_size, layer, block, blocks_at_layer, rotation);
				return;
			}
			const usize stride = block_size >> 2;
			if constexpr(convert_input){
				forward_radix4_block_lazy<true, true>(base, stride, montgomery_one);
			}else if(block == 0){
				forward_radix4_block_lazy<true>(base, stride, montgomery_one);
			}else{
				forward_radix4_block_lazy<false>(base, stride, rotation[layer]);
			}
			
			if(block + 1 < blocks_at_layer){
				rotation[layer] = canonicalize(mul(rotation[layer], forward_rate3(twiddle_index(static_cast<u32>(block)))));
			}
			
			const usize child_size = block_size >> 2;
			if(child_size == leaf_size) return;
			for(usize child = 0; child < 4; ++child){
				forward_cache_dfs<false>(base + child * child_size, child_size, leaf_size, layer + 1, block * 4 + child, blocks_at_layer * 4, rotation);
			}
		}
		
		template <bool convert_input = false>
		EEZ_NTT998_ALWAYS_INLINE void forward_cache_pair_node(mint* EEZ_NTT998_RESTRICT a, mint* EEZ_NTT998_RESTRICT b, usize block_size, unsigned layer, usize block, usize blocks_at_layer, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			const usize stride = block_size >> 2;
			if constexpr(convert_input) forward_radix4_block_pair_lazy<true, true>(a, b, stride, montgomery_one);
			else if(block == 0) forward_radix4_block_pair_lazy<true>(a, b, stride, montgomery_one);
			else forward_radix4_block_pair_lazy<false>(a, b, stride, rotation[layer]);
			if(block + 1 < blocks_at_layer) rotation[layer] = canonicalize(mul(rotation[layer], forward_rate3(twiddle_index(static_cast<u32>(block)))));
		}
		
		template <bool convert_input = false>
		inline void forward_cache_pair_block(mint* EEZ_NTT998_RESTRICT a, mint* EEZ_NTT998_RESTRICT b, usize block_size, unsigned layer, usize block, usize blocks_at_layer, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			forward_cache_pair_node<convert_input>(a, b, block_size, layer, block, blocks_at_layer, rotation);
			const usize child_size = block_size >> 2;
			for(usize child = 0; child < 4; ++child){
				mint* const child_a = a + child * child_size;
				mint* const child_b = b + child * child_size;
				const usize child_block = block * 4 + child;
				forward_cache_pair_node(child_a, child_b, child_size, layer + 1, child_block, blocks_at_layer * 4, rotation);
				const usize grandchild_size = child_size >> 2;
				for(usize grandchild = 0; grandchild < 4; ++grandchild){
					forward_cache_pair_node(child_a + grandchild * grandchild_size, child_b + grandchild * grandchild_size, grandchild_size, layer + 2, child_block * 4 + grandchild, blocks_at_layer * 16, rotation);
				}
			}
		}
		
		template <bool convert_input = false>
		inline void forward_cache_pair_dfs(mint* EEZ_NTT998_RESTRICT a, mint* EEZ_NTT998_RESTRICT b, usize block_size, usize leaf_size, unsigned layer, usize block, usize blocks_at_layer, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			if(block_size == leaf_size * 64){
				forward_cache_pair_block<convert_input>(a, b, block_size, layer, block, blocks_at_layer, rotation);
				return;
			}
			forward_cache_pair_node<convert_input>(a, b, block_size, layer, block, blocks_at_layer, rotation);
			const usize child_size = block_size >> 2;
			if(child_size == leaf_size) return;
			for(usize child = 0; child < 4; ++child){
				forward_cache_pair_dfs<false>(a + child * child_size, b + child * child_size, child_size, leaf_size, layer + 1, block * 4 + child, blocks_at_layer * 4, rotation);
			}
		}
		
		template <bool apply_scale, bool convert_output = false, bool direct_output = false>
		EEZ_NTT998_ALWAYS_INLINE void inverse_cache_node(mint* EEZ_NTT998_RESTRICT base, usize block_size, unsigned layer, usize block, usize blocks_at_layer, word scale, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			const usize stride = block_size >> 2;
			if(block == 0) inverse_radix4_block_lazy<true, apply_scale, convert_output, direct_output>(base, stride, montgomery_one, scale);
			else inverse_radix4_block_lazy<false, apply_scale, convert_output, direct_output>(base, stride, rotation[layer], scale);
			if(block + 1 < blocks_at_layer) rotation[layer] = canonicalize(mul(rotation[layer], inverse_rate3(twiddle_index(static_cast<u32>(block)))));
		}
		
		template <bool scale_leaf, bool convert_output = false, bool direct_output = false>
		inline void inverse_cache_block(mint* EEZ_NTT998_RESTRICT base, usize block_size, unsigned layer, usize block, usize blocks_at_layer, word scale, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			const usize child_size = block_size >> 2;
			const usize grandchild_size = child_size >> 2;
			for(usize child = 0; child < 4; ++child){
				mint* const child_base = base + child * child_size;
				const usize child_block = block * 4 + child;
				for(usize grandchild = 0; grandchild < 4; ++grandchild){
					inverse_cache_node<scale_leaf>(child_base + grandchild * grandchild_size, grandchild_size, layer + 2, child_block * 4 + grandchild, blocks_at_layer * 16, scale, rotation);
				}
				inverse_cache_node<false>(child_base, child_size, layer + 1, child_block, blocks_at_layer * 4, scale, rotation);
			}
			inverse_cache_node<false, convert_output, direct_output>(base, block_size, layer, block, blocks_at_layer, scale, rotation);
		}
		
		template <bool scale_leaf, bool convert_output = false, bool direct_output = false>
		inline void inverse_cache_dfs(mint* EEZ_NTT998_RESTRICT base, usize block_size, usize leaf_size, unsigned layer, usize block, usize blocks_at_layer, word scale, std::array<word, max_log / 2 + 1>& rotation) noexcept {
			if(block_size == leaf_size * 64){
				inverse_cache_block<scale_leaf, convert_output, direct_output>(base, block_size, layer, block, blocks_at_layer, scale, rotation);
				return;
			}
			const usize child_size = block_size >> 2;
			if(child_size != leaf_size){
				for(usize child = 0; child < 4; ++child){
					inverse_cache_dfs<scale_leaf, false>(base + child * child_size, child_size, leaf_size, layer + 1, block * 4 + child, blocks_at_layer * 4, scale, rotation);
				}
			}
			
			const usize stride = block_size >> 2;
			if constexpr(scale_leaf){
				if(child_size == leaf_size){
					if(block == 0) inverse_radix4_block_lazy<true, true, convert_output, direct_output>(base, stride, montgomery_one, scale);
					else inverse_radix4_block_lazy<false, true, convert_output, direct_output>(base, stride, rotation[layer], scale);
				}else if(block == 0){
					inverse_radix4_block_lazy<true, false, convert_output, direct_output>(base, stride, montgomery_one, scale);
				}else{
					inverse_radix4_block_lazy<false, false, convert_output, direct_output>(base, stride, rotation[layer], scale);
				}
			}else if(block == 0){
				inverse_radix4_block_lazy<true, false, convert_output, direct_output>(base, stride, montgomery_one, scale);
			}else{
				inverse_radix4_block_lazy<false, false, convert_output, direct_output>(base, stride, rotation[layer], scale);
			}
			
			if(block + 1 < blocks_at_layer){
				rotation[layer] = canonicalize(mul(rotation[layer], inverse_rate3(twiddle_index(static_cast<u32>(block)))));
			}
		}
		
		EEZ_NTT998_ALWAYS_INLINE void convert_to_montgomery(mint* a, usize n) noexcept {
			constexpr word montgomery_r2 = 932051910u;
			const vec vr2 = broadcast(montgomery_r2);
			const vec vr2_ninv = broadcast(montgomery_r2 * montgomery_ninv);
			for(usize i = 0; i < n; i += 8) store8_aligned(a + i, mul8_fixed(load8_aligned(a + i), vr2, vr2_ninv));
		}
		
		EEZ_NTT998_ALWAYS_INLINE void convert_from_montgomery(mint* a, usize n) noexcept {
			const vec vone = broadcast(1);
			const vec vninv = broadcast(montgomery_ninv);
			for(usize i = 0; i < n; i += 8) store8_aligned(a + i, canonicalize8(mul8_fixed(load8_aligned(a + i), vone, vninv)));
		}
		
		template <bool convert_input = false>
		inline void forward_adaptive(mint* a, usize n, unsigned leaf_log) noexcept {
			const usize leaf_size = usize(1) << leaf_log;
			if(n == leaf_size){
				if constexpr(convert_input) convert_to_montgomery(a, n);
				return;
			}
			std::array<word, max_log / 2 + 1> rotation{};
			rotation.fill(canonicalize(montgomery_one));
			if((std::countr_zero(n) - leaf_log) & 1u){
				forward_radix2_first(a, n);
				if constexpr(convert_input) convert_to_montgomery(a, n);
				forward_cache_dfs(a, n >> 1, leaf_size, 0, 0, 2, rotation);
				forward_cache_dfs(a + (n >> 1), n >> 1, leaf_size, 0, 1, 2, rotation);
				return;
			}
			forward_cache_dfs<convert_input>(a, n, leaf_size, 0, 0, 1, rotation);
		}
		
		template <bool convert_input = false>
		inline void forward_adaptive_pair(mint* EEZ_NTT998_RESTRICT a, mint* EEZ_NTT998_RESTRICT b, usize n, unsigned leaf_log) noexcept {
			const usize leaf_size = usize(1) << leaf_log;
			if(n == leaf_size){
				if constexpr(convert_input){
					convert_to_montgomery(a, n);
					convert_to_montgomery(b, n);
				}
				return;
			}
			std::array<word, max_log / 2 + 1> rotation{};
			rotation.fill(canonicalize(montgomery_one));
			if((std::countr_zero(n) - leaf_log) & 1u){
				forward_radix2_first(a, n);
				forward_radix2_first(b, n);
				if constexpr(convert_input){
					convert_to_montgomery(a, n);
					convert_to_montgomery(b, n);
				}
				forward_cache_pair_dfs(a, b, n >> 1, leaf_size, 0, 0, 2, rotation);
				forward_cache_pair_dfs(a + (n >> 1), b + (n >> 1), n >> 1, leaf_size, 0, 1, 2, rotation);
				return;
			}
			forward_cache_pair_dfs<convert_input>(a, b, n, leaf_size, 0, 0, 1, rotation);
		}
		
		template <bool convert_output = false, bool direct_output = false>
		inline void inverse_adaptive(mint* a, usize n, unsigned leaf_log) noexcept {
			const usize leaf_size = usize(1) << leaf_log;
			if(n == leaf_size){
				if constexpr(convert_output) convert_from_montgomery(a, n);
				return;
			}
			const word scale = mint::raw(static_cast<word>(n >> leaf_log)).inv().a;
			std::array<word, max_log / 2 + 1> rotation{};
			rotation.fill(canonicalize(montgomery_one));
			if((std::countr_zero(n) - leaf_log) & 1u){
				inverse_cache_dfs<true>(a, n >> 1, leaf_size, 0, 0, 2, scale, rotation);
				inverse_cache_dfs<true>(a + (n >> 1), n >> 1, leaf_size, 0, 1, 2, scale, rotation);
				const usize half = n >> 1;
				for(usize i = 0; i < half; i += 8){
					const vec x = shrink4_to_2(load8_aligned(a + i));
					const vec y = shrink4_to_2(load8_aligned(a + half + i));
					vec z0 = lazy_add8(x, y);
					vec z1 = lazy_sub8(x, y);
					if constexpr(convert_output){
						const vec vone = broadcast(1);
						const vec vninv = broadcast(montgomery_ninv);
						z0 = canonicalize8(mul8_fixed(z0, vone, vninv));
						z1 = canonicalize8(mul8_fixed(z1, vone, vninv));
					}else if constexpr(direct_output){
						z0 = canonicalize8(shrink4_to_2(z0));
						z1 = canonicalize8(shrink4_to_2(z1));
					}
					store8_aligned(a + i, z0);
					store8_aligned(a + half + i, z1);
				}
				return;
			}
			inverse_cache_dfs<true, convert_output, direct_output>(a, n, leaf_size, 0, 0, 1, scale, rotation);
		}
		
		EEZ_NTT998_ALWAYS_INLINE __m128i reduce_four_accumulators(vec x) noexcept {
			const vec ninv = broadcast(montgomery_ninv);
			const vec prime = broadcast(mod);
			const vec q = _mm256_mul_epu32(x, ninv);
			const vec sum = _mm256_add_epi64(x, _mm256_mul_epu32(q, prime));
			const vec high = _mm256_bsrli_epi128(sum, 4);
			const vec packed = _mm256_permutevar8x32_epi32(
				high, _mm256_setr_epi32(0, 2, 4, 6, 0, 0, 0, 0)
				);
			return _mm256_castsi256_si128(packed);
		}
		
		EEZ_NTT998_ALWAYS_INLINE vec reduce_eight_accumulators(vec even, vec odd) noexcept {
			const vec ninv = broadcast(montgomery_ninv);
			const vec prime = broadcast(mod);
			const vec q_even = _mm256_mul_epu32(even, ninv);
			const vec q_odd = _mm256_mul_epu32(odd, ninv);
			const vec reduced_even = _mm256_add_epi64(even, _mm256_mul_epu32(q_even, prime));
			const vec reduced_odd = _mm256_add_epi64(odd, _mm256_mul_epu32(q_odd, prime));
			return shrink4_to_2(_mm256_or_si256(_mm256_bsrli_epi128(reduced_even, 4), reduced_odd));
		}
		
		EEZ_NTT998_ALWAYS_INLINE void leaf_product8x4(
			mint* EEZ_NTT998_RESTRICT a,
			mint* EEZ_NTT998_RESTRICT b,
			usize first_block,
			const std::array<word, 4>& modulus
			) noexcept {
				alignas(64) word lhs[4][16];
				alignas(64) vec even[4]{};
				alignas(64) vec odd[4]{};
				
				for(unsigned k = 0; k < 4; ++k){
					const usize offset = (first_block + k) * 8;
					const vec x = canonicalize8(shrink4_to_2(load8_aligned(a + offset)));
					const vec y = canonicalize8(shrink4_to_2(load8_aligned(b + offset)));
					const word w = canonicalize(modulus[k]);
					const vec vw = broadcast(w);
					const vec vwninv = broadcast(w * montgomery_ninv);
					_mm256_store_si256(reinterpret_cast<vec*>(lhs[k]), mul8_fixed(x, vw, vwninv));
					_mm256_store_si256(reinterpret_cast<vec*>(lhs[k] + 8), x);
					store8_aligned(b + offset, y);
				}
				
				for(unsigned i = 0; i < 8; ++i){
					for(unsigned k = 0; k < 4; ++k){
						const usize offset = (first_block + k) * 8;
						const vec y = broadcast(raw(b[offset + i]));
						const vec x = _mm256_loadu_si256(reinterpret_cast<const vec*>(lhs[k] + 8 - i));
						even[k] = _mm256_add_epi64(even[k], _mm256_mul_epu32(y, x));
						odd[k] = _mm256_add_epi64(odd[k], _mm256_mul_epu32(y, _mm256_bsrli_epi128(x, 4)));
					}
				}
				
				for(unsigned k = 0; k < 4; ++k){
					const usize offset = (first_block + k) * 8;
					store8_aligned(a + offset, reduce_eight_accumulators(even[k], odd[k]));
				}
			}
		
		EEZ_NTT998_ALWAYS_INLINE void leaf_product16x2_karatsuba(
			mint* EEZ_NTT998_RESTRICT a,
			const mint* EEZ_NTT998_RESTRICT b,
			usize first_block,
			const std::array<word, 2>& modulus
			) noexcept {
				const vec split = _mm256_setr_epi32(0, 2, 4, 6, 1, 3, 5, 7);
				alignas(64) word lhs[6][16];
				alignas(64) word rhs[6][8];
				alignas(64) vec even[6]{};
				alignas(64) vec odd[6]{};
				word w[2];
				
				for(unsigned k = 0; k < 2; ++k){
					const usize offset = (first_block + k) * 16;
					const vec ax0 = _mm256_permutevar8x32_epi32(canonicalize8(shrink4_to_2(load8_aligned(a + offset))), split);
					const vec ax1 = _mm256_permutevar8x32_epi32(canonicalize8(shrink4_to_2(load8_aligned(a + offset + 8))), split);
					const vec bx0 = _mm256_permutevar8x32_epi32(canonicalize8(shrink4_to_2(load8_aligned(b + offset))), split);
					const vec bx1 = _mm256_permutevar8x32_epi32(canonicalize8(shrink4_to_2(load8_aligned(b + offset + 8))), split);
					const vec ae = _mm256_permute2x128_si256(ax0, ax1, 0x20);
					const vec ao = _mm256_permute2x128_si256(ax0, ax1, 0x31);
					const vec be = _mm256_permute2x128_si256(bx0, bx1, 0x20);
					const vec bo = _mm256_permute2x128_si256(bx0, bx1, 0x31);
					const vec lx[3]{ae, ao, canonicalize8(add8(ae, ao))};
					const vec ry[3]{be, bo, canonicalize8(add8(be, bo))};
					w[k] = canonicalize(modulus[k]);
					const vec vw = broadcast(w[k]);
					const vec vwninv = broadcast(w[k] * montgomery_ninv);
					for(unsigned j = 0; j < 3; ++j){
						const unsigned p = k * 3 + j;
						_mm256_store_si256(reinterpret_cast<vec*>(lhs[p]), mul8_fixed(lx[j], vw, vwninv));
						_mm256_store_si256(reinterpret_cast<vec*>(lhs[p] + 8), lx[j]);
						_mm256_store_si256(reinterpret_cast<vec*>(rhs[p]), ry[j]);
					}
				}
				
				for(unsigned i = 0; i < 8; ++i){
					for(unsigned p = 0; p < 6; ++p){
						const vec y = broadcast(rhs[p][i]);
						const vec x = _mm256_loadu_si256(reinterpret_cast<const vec*>(lhs[p] + 8 - i));
						even[p] = _mm256_add_epi64(even[p], _mm256_mul_epu32(y, x));
						odd[p] = _mm256_add_epi64(odd[p], _mm256_mul_epu32(y, _mm256_bsrli_epi128(x, 4)));
					}
				}
				
				for(unsigned k = 0; k < 2; ++k){
					const vec p0 = reduce_eight_accumulators(even[k * 3], odd[k * 3]);
					const vec p1 = reduce_eight_accumulators(even[k * 3 + 1], odd[k * 3 + 1]);
					const vec p2 = reduce_eight_accumulators(even[k * 3 + 2], odd[k * 3 + 2]);
					vec yp1 = _mm256_permutevar8x32_epi32(p1, _mm256_setr_epi32(7, 0, 1, 2, 3, 4, 5, 6));
					yp1 = _mm256_insert_epi32(yp1, canonicalize(mul(static_cast<word>(_mm256_extract_epi32(p1, 7)), w[k])), 0);
					const vec ce = add8(p0, yp1);
					const vec co = sub8(sub8(p2, p0), p1);
					const vec lo = _mm256_unpacklo_epi32(ce, co);
					const vec hi = _mm256_unpackhi_epi32(ce, co);
					const usize offset = (first_block + k) * 16;
					store8_aligned(a + offset, _mm256_permute2x128_si256(lo, hi, 0x20));
					store8_aligned(a + offset + 8, _mm256_permute2x128_si256(lo, hi, 0x31));
				}
			}
		
		template <unsigned leaf_size, unsigned parallel_blocks>
		inline void leaf_product_group(
			mint* a,
			const mint* b,
			usize first_block,
			const std::array<word, parallel_blocks>& modulus
			) noexcept {
				static_assert(leaf_size == 8 || leaf_size == 16);
				static_assert(leaf_size * parallel_blocks == 32);
				alignas(64) word lhs[parallel_blocks][leaf_size];
				alignas(64) word rhs[parallel_blocks][leaf_size];
				alignas(64) u64 wrapped_rhs[parallel_blocks][2 * leaf_size];
				alignas(64) vec acc[parallel_blocks][leaf_size / 4];
				
				for(unsigned k = 0; k < parallel_blocks; ++k){
					const usize offset = (first_block + k) * leaf_size;
					for(unsigned j = 0; j < leaf_size; j += 8){
						const vec x = canonicalize8(shrink4_to_2(load8_aligned(a + offset + j)));
						const vec y = canonicalize8(shrink4_to_2(load8_aligned(b + offset + j)));
						_mm256_store_si256(reinterpret_cast<vec*>(lhs[k] + j), x);
						_mm256_store_si256(reinterpret_cast<vec*>(rhs[k] + j), y);
					}
					for(unsigned j = 0; j < leaf_size; ++j){
						wrapped_rhs[k][j] = canonicalize(mul(rhs[k][j], modulus[k]));
						wrapped_rhs[k][leaf_size + j] = rhs[k][j];
					}
					for(unsigned j = 0; j < leaf_size / 4; ++j) acc[k][j] = _mm256_setzero_si256();
				}
				
				for(unsigned i = 0; i < leaf_size; ++i){
					for(unsigned k = 0; k < parallel_blocks; ++k){
						const vec x = broadcast(lhs[k][i]);
						for(unsigned j = 0; j < leaf_size; j += 4){
							const vec y = _mm256_loadu_si256(reinterpret_cast<const vec*>(wrapped_rhs[k] + leaf_size - i + j));
							acc[k][j / 4] = _mm256_add_epi64(acc[k][j / 4], _mm256_mul_epu32(x, y));
						}
					}
				}
				
				for(unsigned k = 0; k < parallel_blocks; ++k){
					if constexpr(leaf_size == 16){
						for(unsigned j = 0; j < leaf_size / 4; ++j) acc[k][j] = shrink4_to_2(acc[k][j]);
					}
					__m128i reduced[leaf_size / 4];
					for(unsigned j = 0; j < leaf_size / 4; ++j){
						reduced[j] = reduce_four_accumulators(acc[k][j]);
					}
					const usize offset = (first_block + k) * leaf_size;
					store8_aligned(a + offset, _mm256_set_m128i(reduced[1], reduced[0]));
					if constexpr(leaf_size == 16){
						store8_aligned(a + offset + 8, _mm256_set_m128i(reduced[3], reduced[2]));
					}
				}
			}
		
		template <unsigned leaf_size, unsigned parallel_blocks>
		inline void leaf_products(mint* a, mint* b, usize n) noexcept {
			const usize blocks = n / leaf_size;
			word w = montgomery_one;
			for(usize s = 0; s < blocks; s += parallel_blocks){
				std::array<word, parallel_blocks> modulus{};
				for(unsigned k = 0; k < parallel_blocks; ++k){
					modulus[k] = w;
					const usize block = s + k;
					if(block + 1 < blocks){
						w = mul(w, forward_rate1(twiddle_index(static_cast<u32>(block))));
					}
				}
				if constexpr(leaf_size == 8) leaf_product8x4(a, b, s, modulus);
				else leaf_product16x2_karatsuba(a, b, s, modulus);
			}
		}
		
		inline void convolution_adaptive_inplace(mint* a, mint* b, usize n) noexcept {
			const unsigned leaf_log = adaptive_leaf_log(n);
			forward_adaptive_pair(a, b, n, leaf_log);
			if(leaf_log == 3){
				leaf_products<8, 4>(a, b, n);
			}else{
				leaf_products<16, 2>(a, b, n);
			}
			inverse_adaptive(a, n, leaf_log);
		}
		
		inline void convolution_adaptive_normal_inplace(mint* a, mint* b, usize n) noexcept {
			const unsigned leaf_log = adaptive_leaf_log(n);
			forward_adaptive_pair<true>(a, b, n, leaf_log);
			if(leaf_log == 3){
				leaf_products<8, 4>(a, b, n);
			}else{
				leaf_products<16, 2>(a, b, n);
			}
			inverse_adaptive<true>(a, n, leaf_log);
		}
		
		inline void convolution_adaptive_mixed_normal_inplace(mint* a, mint* b, usize n) noexcept {
			const unsigned leaf_log = adaptive_leaf_log(n);
			forward_adaptive_pair(a, b, n, leaf_log);
			if(leaf_log == 3){
				leaf_products<8, 4>(a, b, n);
			}else{
				leaf_products<16, 2>(a, b, n);
			}
			inverse_adaptive<false, true>(a, n, leaf_log);
		}
		
#endif
		
		inline void pointwise_multiply(mint* EEZ_NTT998_RESTRICT a, const mint* EEZ_NTT998_RESTRICT b, usize n) noexcept {
			usize i = 0;
#if defined(__AVX2__) || defined(_M_AVX2)
			for (; i + 8 <= n; i += 8){
				store8(a + i, mul8(load8(a + i), load8(b + i)));
			}
#endif
			for (; i < n; ++i){
				a[i] = from_raw(mul(raw(a[i]), raw(b[i])));
			}
		}
		
		inline void pointwise_square(mint* EEZ_NTT998_RESTRICT a, usize n) noexcept {
			usize i = 0;
#if defined(__AVX2__) || defined(_M_AVX2)
			for (; i + 8 <= n; i += 8){
				const vec x = load8(a + i);
				store8(a + i, mul8(x, x));
			}
#endif
			for (; i < n; ++i){
				a[i] = from_raw(mul(raw(a[i]), raw(a[i])));
			}
		}
		
	}
	
	inline void forward(std::span<mint> a) noexcept {
		if (a.size() <= 1) return;
		assert(valid_ntt_size(a.size()));
		detail::forward_dif(a.data(), a.size());
	}
	
	inline void inverse(std::span<mint> a) noexcept {
		if (a.size() <= 1) return;
		assert(valid_ntt_size(a.size()));
		detail::inverse_dit(a.data(), a.size());
	}
	
	namespace detail{
		
		inline std::vector<mint> convolution_naive(std::span<const mint> a, std::span<const mint> b){
			std::vector<mint> result(convolution_size(a.size(), b.size()));
			for (usize i = 0; i < a.size(); ++i){
				for (usize j = 0; j < b.size(); ++j){
					result[i + j] += a[i] * b[j];
				}
			}
			return result;
		}
		
		inline std::vector<mint> square_naive(std::span<const mint> a){
			std::vector<mint> result(convolution_size(a.size(), a.size()));
			for (usize i = 0; i < a.size(); ++i){
				result[2 * i] += a[i] * a[i];
				for (usize j = i + 1; j < a.size(); ++j){
					const mint product = a[i] * a[j];
					result[i + j] += product + product;
				}
			}
			return result;
		}
		
		inline usize checked_transform_size(usize n, usize m){
			const usize result = transform_size(n, m);
			if (n && m && !result){
				throw std::length_error("eez::ntt998: convolution exceeds the 2^23 transform limit");
			}
			return result;
		}
		
		inline void require_ntt_size(usize n){
			if (!valid_ntt_size(n)){
				throw std::invalid_argument("eez::ntt998: transform length must be a power of two in [1, 2^23]");
			}
		}
		
	}
	
	inline std::vector<mint> convolution(std::span<const mint> a, std::span<const mint> b){
		if (a.empty() || b.empty()) return {};
		if (a.data() == b.data() && a.size() == b.size()) return square(a);
		if (std::min(a.size(), b.size()) <= naive_cutoff){
			return detail::convolution_naive(a, b);
		}
		
		const usize result_size = convolution_size(a.size(), b.size());
		const usize n = detail::checked_transform_size(a.size(), b.size());
		std::vector<mint> fa(n);
		std::vector<mint> fb(n);
		std::copy(a.begin(), a.end(), fa.begin());
		std::copy(b.begin(), b.end(), fb.begin());
		
		detail::forward_dif_partial(fa.data(), n);
		detail::forward_dif_partial(fb.data(), n);
		detail::block_convolution4(fa.data(), fb.data(), n);
		detail::inverse_dit_partial(fa.data(), n);
		fa.resize(result_size);
		return fa;
	}
	
	inline std::vector<mint> square(std::span<const mint> a){
		if (a.empty()) return {};
		if (a.size() <= naive_cutoff) return detail::square_naive(a);
		
		const usize result_size = convolution_size(a.size(), a.size());
		const usize n = detail::checked_transform_size(a.size(), a.size());
#if defined(__GNUC__) || defined(__clang__)
		if (n < a.size()) __builtin_unreachable();
#endif
		std::vector<mint> fa(n);
		std::copy(a.begin(), a.end(), fa.begin());
		
		detail::forward_dif_partial(fa.data(), n);
		detail::block_square4(fa.data(), n);
		detail::inverse_dit_partial(fa.data(), n);
		fa.resize(result_size);
		return fa;
	}
	
	inline void convolution_to(std::span<const mint> a, std::span<const mint> b, std::span<mint> out, workspace& ws){
		if (a.empty() || b.empty()) return;
		const usize result_size = convolution_size(a.size(), b.size());
		if (out.size() < result_size){
			throw std::invalid_argument("eez::ntt998::convolution_to: output span is too small");
		}
		
		if (a.data() == b.data() && a.size() == b.size()){
			square_to(a, out, ws);
			return;
		}
		
		if (std::min(a.size(), b.size()) <= naive_cutoff){
			std::fill_n(out.begin(), result_size, mint{});
			for (usize i = 0; i < a.size(); ++i){
				for (usize j = 0; j < b.size(); ++j){
					out[i + j] += a[i] * b[j];
				}
			}
			return;
		}
		
		const usize n = detail::checked_transform_size(a.size(), b.size());
		ws.reserve(n);
		std::fill_n(ws.a_.begin(), n, mint{});
		std::fill_n(ws.b_.begin(), n, mint{});
		std::copy(a.begin(), a.end(), ws.a_.begin());
		std::copy(b.begin(), b.end(), ws.b_.begin());
		
		detail::forward_dif_partial(ws.a_.data(), n);
		detail::forward_dif_partial(ws.b_.data(), n);
		detail::block_convolution4(ws.a_.data(), ws.b_.data(), n);
		detail::inverse_dit_partial(ws.a_.data(), n);
		std::copy_n(ws.a_.begin(), result_size, out.begin());
	}
	
	inline void square_to(std::span<const mint> a, std::span<mint> out, workspace& ws){
		if (a.empty()) return;
		const usize result_size = convolution_size(a.size(), a.size());
		if (out.size() < result_size){
			throw std::invalid_argument("eez::ntt998::square_to: output span is too small");
		}
		
		if (a.size() <= naive_cutoff){
			std::fill_n(out.begin(), result_size, mint{});
			for (usize i = 0; i < a.size(); ++i){
				out[2 * i] += a[i] * a[i];
				for (usize j = i + 1; j < a.size(); ++j){
					const mint product = a[i] * a[j];
					out[i + j] += product + product;
				}
			}
			return;
		}
		
		const usize n = detail::checked_transform_size(a.size(), a.size());
		ws.reserve(n);
		std::fill_n(ws.a_.begin(), n, mint{});
		std::copy(a.begin(), a.end(), ws.a_.begin());
		
		detail::forward_dif_partial(ws.a_.data(), n);
		detail::block_square4(ws.a_.data(), n);
		detail::inverse_dit_partial(ws.a_.data(), n);
		std::copy_n(ws.a_.begin(), result_size, out.begin());
	}
	
	inline void forward_to(std::span<const mint> src, frequency_buffer& dst, usize n){
		detail::require_ntt_size(n);
		if (src.size() > n){
			throw std::invalid_argument("eez::ntt998::forward_to: source is longer than transform");
		}
		
		dst.data_.assign(n, mint{});
		std::copy(src.begin(), src.end(), dst.data_.begin());
		detail::forward_dif(dst.data_.data(), n);
	}
	
	inline void pointwise_multiply(frequency_buffer& lhs, const frequency_buffer& rhs){
		if (lhs.size() != rhs.size()){
			throw std::invalid_argument("eez::ntt998::pointwise_multiply: transform sizes differ");
		}
		detail::pointwise_multiply(lhs.data_.data(), rhs.data_.data(), lhs.data_.size());
	}
	
	inline void pointwise_square(frequency_buffer& a){
		detail::pointwise_square(a.data_.data(), a.data_.size());
	}
	
	inline void inverse_to(frequency_buffer& src, std::span<mint> out){
		if (src.data_.empty()){
			if (!out.empty()){
				throw std::invalid_argument("eez::ntt998::inverse_to: empty transform");
			}
			return;
		}
		if (out.size() > src.data_.size()){
			throw std::invalid_argument("eez::ntt998::inverse_to: output is longer than transform");
		}
		
		detail::inverse_dit(src.data_.data(), src.data_.size());
		std::copy_n(src.data_.begin(), out.size(), out.begin());
	}
	
}

#undef EEZ_NTT998_ALWAYS_INLINE
#undef EEZ_NTT998_RESTRICT
#line 1 "fastio_unsafe.hpp"
#line 2 "IO/fastio_unsafe.hpp"

#line 11 "fastio_unsafe.hpp"

#ifdef __linux__
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#endif

#ifndef FASTIO_UNSAFE_BLOCK_LOG
#define FASTIO_UNSAFE_BLOCK_LOG 14
#endif

namespace fastio_unsafe_impl {
	
	using i32 = std::int32_t;
	using u32 = std::uint32_t;
	using i64 = std::int64_t;
	using u64 = std::uint64_t;
	using i128 = __int128_t;
	using u128 = __uint128_t;
	
	constexpr auto make_right_align_masks() {
		std::array<std::array<char, 16>, 16> masks{};
		for (int digits = 0; digits < 16; ++digits) {
			for (int i = 0; i < 16; ++i) {
				masks[digits][i] = i < 16 - digits
				? static_cast<char>(0x80)
				: static_cast<char>(i - (16 - digits));
			}
		}
		return masks;
	}
	
	constexpr auto make_powers_10() {
		std::array<u64, 17> powers{};
		powers[0] = 1;
		for (std::size_t i = 1; i < powers.size(); ++i) {
			powers[i] = powers[i - 1] * 10;
		}
		return powers;
	}
	
	alignas(16) inline constexpr auto right_align_masks = make_right_align_masks();
	inline constexpr auto powers_10 = make_powers_10();
	
	struct input {
		input() {
#ifdef __linux__
			struct stat info {};
			if (::fstat(0, &info) == 0 && S_ISREG(info.st_mode) && info.st_size > 0) {
				const off_t current = ::lseek(0, 0, SEEK_CUR);
				const std::size_t file_size = static_cast<std::size_t>(info.st_size);
				const std::size_t page_size = static_cast<std::size_t>(::sysconf(_SC_PAGESIZE));
				const std::size_t rounded_size =
				(file_size + page_size - 1) / page_size * page_size;
				const std::size_t reserved_size = rounded_size + page_size;
				
				char* region = static_cast<char*>(::mmap(
					nullptr, reserved_size, PROT_NONE,
					MAP_PRIVATE | MAP_ANONYMOUS, -1, 0));
				if (region != MAP_FAILED) {
					void* file_mapping = ::mmap(
						region, rounded_size, PROT_READ,
						MAP_PRIVATE | MAP_FIXED, 0, 0);
					void* zero_page = file_mapping == MAP_FAILED ? MAP_FAILED : ::mmap(
						region + rounded_size, page_size, PROT_READ,
						MAP_PRIVATE | MAP_ANONYMOUS | MAP_FIXED, -1, 0);
					if (file_mapping != MAP_FAILED && zero_page != MAP_FAILED) {
						const std::size_t offset = current > 0
						? std::min(static_cast<std::size_t>(current), file_size)
						: 0;
						cursor_ = region + offset;
						return;
					}
					::munmap(region, reserved_size);
				}
			}
#endif
			read_all_fallback();
		}
		
		input(const input&) = delete;
		input& operator=(const input&) = delete;
		
		char* cursor() const noexcept { return cursor_; }
		
	private:
		void read_all_fallback() {
			std::size_t capacity = 1u << 20;
			std::size_t size = 0;
			char* buffer = static_cast<char*>(std::malloc(capacity + 64));
			if (buffer == nullptr) std::abort();
			
			for (;;) {
				if (size == capacity) {
					capacity *= 2;
					char* grown = static_cast<char*>(std::realloc(buffer, capacity + 64));
					if (grown == nullptr) std::abort();
					buffer = grown;
				}
				const std::size_t count = std::fread(
					buffer + size, 1, capacity - size, stdin);
				size += count;
				if (count == 0) break;
			}
			std::memset(buffer + size, 0, 64);
			cursor_ = buffer;
		}
		
		char* cursor_ = nullptr;
	};
	
	__attribute__((always_inline)) inline u64 parse_16_digits(__m128i digits) noexcept {
		const __m128i pair_weights = _mm_set1_epi16(0x010A);
		const __m128i quad_weights = _mm_set1_epi32(0x00010064);
		const __m128i oct_weights = _mm_set_epi32(1, 10000, 1, 10000);
		const __m128i pairs = _mm_maddubs_epi16(digits, pair_weights);
		const __m128i quads = _mm_madd_epi16(pairs, quad_weights);
		const __m128i products = _mm_mul_epu32(quads, oct_weights);
		const __m128i odd = _mm_srli_epi64(quads, 32);
		const __m128i octets = _mm_add_epi64(products, odd);
		const u64 high = static_cast<u64>(_mm_cvtsi128_si64(octets));
		const u64 low = static_cast<u64>(_mm_extract_epi64(octets, 1));
		return high * 100000000ULL + low;
	}
	
	__attribute__((always_inline)) inline __m128i load_digits(const char* cursor) noexcept {
		return _mm_sub_epi8(
			_mm_loadu_si128(reinterpret_cast<const __m128i*>(cursor)),
			_mm_set1_epi8('0'));
	}
	
	__attribute__((always_inline)) inline u64 parse_short_digits(
		__m128i digits, u32 mask, int& length) noexcept {
			length = __builtin_ctz(mask);
			digits = _mm_shuffle_epi8(
				digits,
				_mm_load_si128(reinterpret_cast<const __m128i*>(
					right_align_masks[static_cast<std::size_t>(length)].data())));
			return parse_16_digits(digits);
		}
	
	__attribute__((always_inline)) inline u32 read_u32(char*& cursor) noexcept {
		const __m128i digits = load_digits(cursor);
		const u32 mask = static_cast<u32>(_mm_movemask_epi8(digits));
		int length;
		const u32 value = static_cast<u32>(parse_short_digits(digits, mask, length));
		cursor += length + 1;
		return value;
	}
	
	__attribute__((always_inline)) inline i32 read_i32(char*& cursor) noexcept {
		const bool negative = *cursor == '-';
		cursor += static_cast<unsigned>(negative);
		const u32 magnitude = read_u32(cursor);
		const u32 bits = negative ? u32{0} - magnitude : magnitude;
		return static_cast<i32>(bits);
	}
	
	__attribute__((always_inline)) inline u64 read_u64(char*& cursor) noexcept {
		__m128i digits = load_digits(cursor);
		const u32 mask = static_cast<u32>(_mm_movemask_epi8(digits));
		
		if (__builtin_expect(mask != 0, 1)) {
			int length;
			const u64 value = parse_short_digits(digits, mask, length);
			cursor += length + 1;
			return value;
		}
		
		u64 value = parse_16_digits(digits);
		cursor += 16;
		while (*cursor >= '0') {
			value = value * 10 + static_cast<unsigned>(*cursor & 15);
			++cursor;
		}
		++cursor;
		return value;
	}
	
	__attribute__((always_inline)) inline i64 read_i64(char*& cursor) noexcept {
		const bool negative = *cursor == '-';
		cursor += static_cast<unsigned>(negative);
		const u64 magnitude = read_u64(cursor);
		const u64 bits = negative ? u64{0} - magnitude : magnitude;
		return static_cast<i64>(bits);
	}
	
	__attribute__((always_inline)) inline u128 read_u128(char*& cursor) noexcept {
		__m128i digits = load_digits(cursor);
		u32 mask = static_cast<u32>(_mm_movemask_epi8(digits));
		
		if (__builtin_expect(mask != 0, 0)) {
			int length;
			const u128 value = parse_short_digits(digits, mask, length);
			cursor += length + 1;
			return value;
		}
		
		u128 value = parse_16_digits(digits);
		cursor += 16;
		
		digits = load_digits(cursor);
		mask = static_cast<u32>(_mm_movemask_epi8(digits));
		if (mask != 0) {
			int length;
			const u64 tail = parse_short_digits(digits, mask, length);
			cursor += length + 1;
			return value * powers_10[static_cast<std::size_t>(length)] + tail;
		}
		
		value = value * static_cast<u128>(10000000000000000ULL)
		+ parse_16_digits(digits);
		cursor += 16;
		
		digits = load_digits(cursor);
		mask = static_cast<u32>(_mm_movemask_epi8(digits));
		int length;
		const u64 tail = parse_short_digits(digits, mask, length);
		cursor += length + 1;
		return value * powers_10[static_cast<std::size_t>(length)] + tail;
	}
	
	__attribute__((always_inline)) inline i128 read_i128(char*& cursor) noexcept {
		const bool negative = *cursor == '-';
		cursor += static_cast<unsigned>(negative);
		const u128 magnitude = read_u128(cursor);
		const u128 bits = negative ? u128{0} - magnitude : magnitude;
		return static_cast<i128>(bits);
	}
	
	constexpr u32 pack4(char a, char b, char c, char d) noexcept {
		return static_cast<u32>(static_cast<unsigned char>(a)) |
		(static_cast<u32>(static_cast<unsigned char>(b)) << 8) |
		(static_cast<u32>(static_cast<unsigned char>(c)) << 16) |
		(static_cast<u32>(static_cast<unsigned char>(d)) << 24);
	}
	
	constexpr auto make_padded_groups() {
		std::array<u32, 10000> table{};
		for (int value = 0; value < 10000; ++value) {
			table[static_cast<std::size_t>(value)] = pack4(
				static_cast<char>('0' + value / 1000),
				static_cast<char>('0' + value / 100 % 10),
				static_cast<char>('0' + value / 10 % 10),
				static_cast<char>('0' + value % 10));
		}
		return table;
	}
	
	inline constexpr auto padded_groups = make_padded_groups();
	
	struct output {
		output() = default;
		output(const output&) = delete;
		output& operator=(const output&) = delete;
		
		char* begin() noexcept { return buffer_.data(); }
		char* end() noexcept { return buffer_.data() + buffer_.size(); }
		
		__attribute__((noinline)) char* flush(char* cursor) noexcept {
			std::size_t remaining = static_cast<std::size_t>(cursor - buffer_.data());
			const char* data = buffer_.data();
			
			if (first_flush_ && remaining != 0) {
				++data;
				--remaining;
				first_flush_ = false;
			}
#ifdef __linux__
			while (remaining != 0) {
				const ssize_t count = ::write(1, data, remaining);
				if (count > 0) {
					data += count;
					remaining -= static_cast<std::size_t>(count);
				} else if (count < 0 && errno == EINTR) {
					continue;
				} else {
					std::abort();
				}
			}
#else
			while (remaining != 0) {
				const std::size_t count = std::fwrite(data, 1, remaining, stdout);
				if (count == 0) std::abort();
				data += count;
				remaining -= count;
			}
#endif
			return buffer_.data();
		}
		
		void finish(char* cursor) noexcept {
			if (cursor != buffer_.data() || !first_flush_) *cursor++ = '\n';
			(void)flush(cursor);
		}
		
		alignas(64) std::array<char, 1u << 19> buffer_;
		bool first_flush_ = true;
	};
	
	__attribute__((always_inline)) inline void store_group(
		char*& cursor, u32 group) noexcept {
			std::memcpy(cursor, &group, sizeof(group));
			cursor += sizeof(group);
		}
	
	__attribute__((always_inline)) inline void emit_leading(
		char*& cursor, u64 value) noexcept {
			const unsigned skip =
			3u
			- static_cast<unsigned>(value >= 10)
			- static_cast<unsigned>(value >= 100)
			- static_cast<unsigned>(value >= 1000);
			const u32 group =
			padded_groups[static_cast<std::size_t>(value)] >> (skip * 8);
			std::memcpy(cursor, &group, sizeof(group));
			cursor += 4 - skip;
		}
	
	__attribute__((always_inline)) inline void emit_padded(
		char*& cursor, u64 value) noexcept {
			store_group(cursor, padded_groups[static_cast<std::size_t>(value)]);
		}
	
	__attribute__((always_inline)) inline void emit_padded_16(
		char*& cursor, u64 value) noexcept {
			emit_padded(cursor, value / 1000000000000ULL);
			emit_padded(cursor, value / 100000000ULL % 10000);
			emit_padded(cursor, value / 10000ULL % 10000);
			emit_padded(cursor, value % 10000);
		}
	
	__attribute__((always_inline)) inline void emit_u32_unchecked(
		char*& cursor, u32 value) noexcept {
			if (value >= 100000000U) {
				emit_leading(cursor, value / 100000000U);
				emit_padded(cursor, value / 10000U % 10000);
				emit_padded(cursor, value % 10000);
			} else if (value >= 10000U) {
				emit_leading(cursor, value / 10000U);
				emit_padded(cursor, value % 10000);
			} else {
				emit_leading(cursor, value);
			}
		}
	
	__attribute__((always_inline)) inline void emit_u64_unchecked(
		char*& cursor, u64 value) noexcept {
			if (value >= 10000000000000000ULL) {
				emit_leading(cursor, value / 10000000000000000ULL);
				emit_padded_16(cursor, value % 10000000000000000ULL);
			} else if (value >= 1000000000000ULL) {
				emit_leading(cursor, value / 1000000000000ULL);
				emit_padded(cursor, value / 100000000ULL % 10000);
				emit_padded(cursor, value / 10000ULL % 10000);
				emit_padded(cursor, value % 10000);
			} else if (value >= 100000000ULL) {
				emit_leading(cursor, value / 100000000ULL);
				emit_padded(cursor, value / 10000ULL % 10000);
				emit_padded(cursor, value % 10000);
			} else if (value >= 10000ULL) {
				emit_leading(cursor, value / 10000);
				emit_padded(cursor, value % 10000);
			} else {
				emit_leading(cursor, value);
			}
		}
	
	__attribute__((always_inline)) inline void emit_u128_unchecked(
		char*& cursor, u128 value) noexcept {
			constexpr u128 base = static_cast<u128>(10000000000000000ULL);
			constexpr u128 u64_max = static_cast<u128>(~u64{0});
			
			if (value <= u64_max) {
				emit_u64_unchecked(cursor, static_cast<u64>(value));
				return;
			}
			
			const u64 low = static_cast<u64>(value % base);
			const u128 upper = value / base;
			if (upper <= u64_max) {
				emit_u64_unchecked(cursor, static_cast<u64>(upper));
				emit_padded_16(cursor, low);
				return;
			}
			
			const u64 middle = static_cast<u64>(upper % base);
			const u32 high = static_cast<u32>(upper / base);
			emit_u32_unchecked(cursor, high);
			emit_padded_16(cursor, middle);
			emit_padded_16(cursor, low);
		}
	
	__attribute__((always_inline)) inline void write_u32(
		output& sink, char*& cursor, char* end, u32 value) noexcept {
			if (__builtin_expect(end - cursor < 16, 0)) cursor = sink.flush(cursor);
			*cursor++ = ' ';
			emit_u32_unchecked(cursor, value);
		}
	
	__attribute__((always_inline)) inline void write_i32(
		output& sink, char*& cursor, char* end, i32 value) noexcept {
			if (__builtin_expect(end - cursor < 16, 0)) cursor = sink.flush(cursor);
			const bool negative = value < 0;
			const u32 bits = static_cast<u32>(value);
			const u32 magnitude = negative ? u32{0} - bits : bits;
			*cursor++ = ' ';
			if (negative) *cursor++ = '-';
			emit_u32_unchecked(cursor, magnitude);
		}
	
	__attribute__((always_inline)) inline void write_u64(
		output& sink, char*& cursor, char* end, u64 value) noexcept {
			if (__builtin_expect(end - cursor < 24, 0)) cursor = sink.flush(cursor);
			*cursor++ = ' ';
			emit_u64_unchecked(cursor, value);
		}
	
	__attribute__((always_inline)) inline void write_i64(
		output& sink, char*& cursor, char* end, i64 value) noexcept {
			if (__builtin_expect(end - cursor < 24, 0)) cursor = sink.flush(cursor);
			const bool negative = value < 0;
			const u64 bits = static_cast<u64>(value);
			const u64 magnitude = negative ? u64{0} - bits : bits;
			*cursor++ = ' ';
			if (negative) *cursor++ = '-';
			emit_u64_unchecked(cursor, magnitude);
		}
	
	__attribute__((always_inline)) inline void write_u128(
		output& sink, char*& cursor, char* end, u128 value) noexcept {
			if (__builtin_expect(end - cursor < 48, 0)) cursor = sink.flush(cursor);
			*cursor++ = ' ';
			emit_u128_unchecked(cursor, value);
		}
	
	__attribute__((always_inline)) inline void write_i128(
		output& sink, char*& cursor, char* end, i128 value) noexcept {
			if (__builtin_expect(end - cursor < 48, 0)) cursor = sink.flush(cursor);
			const bool negative = value < 0;
			const u128 bits = static_cast<u128>(value);
			const u128 magnitude = negative ? u128{0} - bits : bits;
			*cursor++ = ' ';
			if (negative) *cursor++ = '-';
			emit_u128_unchecked(cursor, magnitude);
		}
	
}

struct fastio_unsafe {
	using i32 = fastio_unsafe_impl::i32;
	using u32 = fastio_unsafe_impl::u32;
	using i64 = fastio_unsafe_impl::i64;
	using u64 = fastio_unsafe_impl::u64;
	using i128 = fastio_unsafe_impl::i128;
	using u128 = fastio_unsafe_impl::u128;
	
	fastio_unsafe() = default;
	fastio_unsafe(const fastio_unsafe&) = delete;
	fastio_unsafe& operator=(const fastio_unsafe&) = delete;
	
	char* input_cursor() const noexcept { return in.cursor(); }
	char* output_cursor() noexcept { return out.begin(); }
	char* output_end() noexcept { return out.end(); }
	void finish(char* cursor) noexcept { out.finish(cursor); }
	
	__attribute__((always_inline)) u32 read_u32(char*& cursor) noexcept {
		return fastio_unsafe_impl::read_u32(cursor);
	}
	__attribute__((always_inline)) i32 read_i32(char*& cursor) noexcept {
		return fastio_unsafe_impl::read_i32(cursor);
	}
	__attribute__((always_inline)) u64 read_u64(char*& cursor) noexcept {
		return fastio_unsafe_impl::read_u64(cursor);
	}
	__attribute__((always_inline)) i64 read_i64(char*& cursor) noexcept {
		return fastio_unsafe_impl::read_i64(cursor);
	}
	__attribute__((always_inline)) u128 read_u128(char*& cursor) noexcept {
		return fastio_unsafe_impl::read_u128(cursor);
	}
	__attribute__((always_inline)) i128 read_i128(char*& cursor) noexcept {
		return fastio_unsafe_impl::read_i128(cursor);
	}
	
	__attribute__((always_inline)) void write_u32(
		char*& cursor, char* end, u32 value) noexcept {
			fastio_unsafe_impl::write_u32(out, cursor, end, value);
		}
	__attribute__((always_inline)) void write_i32(
		char*& cursor, char* end, i32 value) noexcept {
			fastio_unsafe_impl::write_i32(out, cursor, end, value);
		}
	__attribute__((always_inline)) void write_u64(
		char*& cursor, char* end, u64 value) noexcept {
			fastio_unsafe_impl::write_u64(out, cursor, end, value);
		}
	__attribute__((always_inline)) void write_i64(
		char*& cursor, char* end, i64 value) noexcept {
			fastio_unsafe_impl::write_i64(out, cursor, end, value);
		}
	__attribute__((always_inline)) void write_u128(
		char*& cursor, char* end, u128 value) noexcept {
			fastio_unsafe_impl::write_u128(out, cursor, end, value);
		}
	__attribute__((always_inline)) void write_i128(
		char*& cursor, char* end, i128 value) noexcept {
			fastio_unsafe_impl::write_i128(out, cursor, end, value);
		}
	
	fastio_unsafe_impl::input in;
	fastio_unsafe_impl::output out;
};
#line 9 "convolution_v4.cpp"

constexpr auto make_mod998_pair_digits(){
	std::array<fastio_unsafe_impl::u32,1<<14> table{};
	table.fill(255);
	for(unsigned a=0;a<10;++a){
		for(unsigned b=0;b<10;++b){
			table[('0'+a)|(('0'+b)<<8)]=a*10+b;
		}
	}
	return table;
}

inline constexpr auto mod998_pair_digits=make_mod998_pair_digits();

__attribute__((always_inline)) inline fastio_unsafe_impl::u32 read_mod998_u32(char*& cursor) noexcept {
	const auto q0=mod998_pair_digits[*reinterpret_cast<const std::uint16_t*>(cursor+1)];
	const auto q1=mod998_pair_digits[*reinterpret_cast<const std::uint16_t*>(cursor+3)];
	const auto q2=mod998_pair_digits[*reinterpret_cast<const std::uint16_t*>(cursor+5)];
	const auto q3=mod998_pair_digits[*reinterpret_cast<const std::uint16_t*>(cursor+7)];
	if(__builtin_expect((q0|q1|q2|q3)<128,1)){
		fastio_unsafe_impl::u32 value=static_cast<unsigned char>(cursor[0])-'0';
		value=value*100+q0;
		value=value*100+q1;
		value=value*100+q2;
		value=value*100+q3;
		cursor+=10;
		return value;
	}
	fastio_unsafe_impl::u32 value=static_cast<unsigned char>(*cursor++)-'0';
	for(unsigned i=0;i<4;++i){
		const auto pair=mod998_pair_digits[*reinterpret_cast<const std::uint16_t*>(cursor)];
		if(pair>99) break;
		value=value*100+pair;
		cursor+=2;
	}
	if(*cursor>' ') value=value*10+static_cast<unsigned>(*cursor++&15);
	++cursor;
	return value;
}

__attribute__((always_inline)) inline void write_mod998(
	fastio_unsafe_impl::output& sink,
	char*& cursor,
	char* end,
	fastio_unsafe_impl::u32 value
	) noexcept {
		if(__builtin_expect(end-cursor<16,0)) cursor=sink.flush(cursor);
		*cursor++=' ';
		if(value>=100000000U){
			const fastio_unsafe_impl::u32 high=value/100000000U;
			*cursor++=static_cast<char>('0'+high);
			value-=high*100000000U;
			fastio_unsafe_impl::emit_padded(cursor,value/10000U);
			fastio_unsafe_impl::emit_padded(cursor,value%10000U);
		}else{
			fastio_unsafe_impl::emit_u32_unchecked(cursor,value);
		}
	}

using mint=eez::ntt998::mint;

void solve(){
	i64 n, k;
	std::cin >> n >> k;
	
	std::vector<std::vector<mint>> r;
	for (int i = 0; i < n - 1; ++i) {
		r.push_back({1, i, 1});
		while (r.size() >= 2 && r[r.size() - 1].size() >= r[r.size() - 2].size()) {
			auto x = r[r.size() - 2], y = r[r.size() - 1];
			r.pop_back();
			r.pop_back();
			r.push_back(eez::ntt998::convolution(x, y));
		}
	}
	while (r.size() >= 2) {
		auto x = r[r.size() - 2], y = r[r.size() - 1];
		r.pop_back();
		r.pop_back();
		r.push_back(eez::ntt998::convolution(x, y));
	}
	
	mint ans = 0;
	for (int i = n + k - 1; i < 2 * n - 1; ++i) {
		ans += r[0][i];
	}
	std::cout << ans << "\n";
}

int main() {
	ios::sync_with_stdio( 0 );
	cin.tie( 0 );
	cout.tie( 0 );
	
  	cin >> tt;	//非多组测试数据时注释掉即可
	
	while ( tt-- ) {
		solve();
//		cout.flush();
	}
	cout.flush();
	
	return 0;
}
