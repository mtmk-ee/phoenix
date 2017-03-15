//
//  Time.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/8/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef Time_hpp
#define Time_hpp

namespace phoenix {
	namespace scripting { class Script; }
	
	
	
	
	/** A high-precision time */
	typedef class Duration {
		unsigned long long nanoseconds;
		
	public:
		/** Zero time */
		inline Duration() : nanoseconds(0) {
			
		}
		/** Time in nanoseconds */
		inline Duration(unsigned long long nanoseconds) : nanoseconds(nanoseconds) {
			
		}
		
		
		/** Returns the current time */
		static Duration Now();
		/** Returns a duration of zero */
		static inline Duration Zero() {
			return Duration();
		}
		
		
		static void Wrap(scripting::Script *script);
		
		
		
		/** Returns the time in nanoseconds */
		inline unsigned long long Nanoseconds() const {
			return nanoseconds;
		}
		/** Returns the time in milliseconds */
		inline double Milliseconds()       const {
			return (long double)nanoseconds / 1e6;
		}
		/** Returns the time in second */
		inline double Seconds()            const {
			return nanoseconds / 1e9;
		}
		/** Returns the time in minutes */
		inline double Minutes()            const {
			return (long double)nanoseconds / 60e9;
		}
		/** Returns the time in hours */
		inline double Hours()              const {
			return (long double)nanoseconds / 36e11;
		}
		
		
		/* Operators */
		inline Duration operator +(const Duration &other) const {
			return nanoseconds + other.nanoseconds;
		}
		inline Duration operator -(const Duration &other) const {
			return nanoseconds - other.nanoseconds;
		}
		inline Duration operator *(double scalar)                      const {
			return (unsigned long long)(nanoseconds * scalar);
		}
		inline Duration operator /(double inv_scalar)                  const {
			return (inv_scalar == 0) ? 0 : (unsigned long long)(nanoseconds / inv_scalar);
		}
		
		inline Duration &operator +=(const Duration &other)     {
			nanoseconds += other.nanoseconds;
			return *this;
		}
		inline Duration &operator -=(const Duration &other)     {
			nanoseconds -= other.nanoseconds;
			return *this;
		}
		inline Duration &operator *=(double scalar)                          {
			nanoseconds *= scalar;
			return *this;
		}
		inline Duration &operator /=(double inv_scalar)                      {
			if ( inv_scalar == 0 ) nanoseconds = 0;
			else nanoseconds /= inv_scalar;
			return *this;
		}
		
	} Time;
	
	
	
	
	
	
	
	
	
	/** A timer class */
	class Timer {
		Time start_time;
		
	public:
		inline Timer() {
			
		}
		
		
		/** Starts the timer */
		inline void Start()       {
			start_time = Time::Now();
		}
		/** Returns the current time on this timer */
		inline Duration GetTime() const {
			return Time::Now() - start_time;
		}
	};
	

	
	
	
	
}

#endif /* Time_hpp */
