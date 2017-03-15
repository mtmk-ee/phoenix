//
//  File.hpp
//  ShooterGame
//
//  Created by Mitchell Matsumori-Kelly on 2/12/17.
//  Copyright © 2017 Phoenix. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <string>
#include <vector>
#include <fstream>


namespace phoenix {
	namespace scripting { class Script; }
	
	
	
	/** A file */
	class File {
	private:
		std::string path;
		
		
	public:
		/** Constructs a File object describing the user's home directory */
		File();
		/** Constructs a File object */
		File(const std::string &path);
		
		
		/** Returns the filepath */
		inline const std::string &GetPath() const {
			return path;
		}
		/** Checks if this file is a directory */
		bool IsDirectory() const;
		/** Checks if this file exists */
		bool Exists() const;
		
		void MakeDirectory() const;
		
		
		/** Returns the parent file */
		inline File GetParent() const {
			auto find_pos = path.rfind('/');
			if ( find_pos == std::string::npos ) return *this;
			else return path.substr(0, find_pos);
		}
		/** Returns a child file */
		inline File GetChild(const std::string &child_name) const {
			return File(path + "/" + child_name);
		}
		
		
		/** Returns the name of the file (excluding extension) */
		inline std::string GetName() const {
			std::string name_and_ext = path.substr(path.find_last_of("/") + 1);
			return name_and_ext.substr(0, name_and_ext.find_first_of("."));
		}
		
		
		
		
		/** Equality check */
		inline bool operator == (const File &other) const {
			return path == other.path;
		}
		/** Concatenation */
		inline File operator + (const std::string &child_name) const {
			return File(path + '/' + child_name);
		}
		/** Concatenation + Assignment */
		inline File &operator +=(const std::string &child_name) {
			path = path + '/' + child_name;
			return *this;
		}
		
		
		/** Attempts to write a string to the file */
		bool WriteText(const std::string &text, bool append = false) const;
		/** Reads text from this file */
		std::string ReadText(bool *fail_check = nullptr) const;
		/** Reads lines of text from this file */
		std::vector<std::string> ReadLines() const;
		/** Returns a list of child files */
		std::vector<File> GetChildren() const;
		
		
		/** Cast operator to string */
		inline operator const char*() const {
			return GetPath().c_str();
		}
		
		
		static void Wrap(scripting::Script *script);
	};
	
	
	
	
	
	
	
	
	
	
	
	/** A file output stream, modeled after Java's DataOutputStream class */
	class FileOutputStream {
		typedef char byte;
		
		std::fstream output_stream;
		bool open;
		
		
		/** Writes an array */
		template <typename T> inline void WriteArray(const T *t, long size) {
			WriteLong(size); // Write the size of the array
			output_stream.write((char*)t, sizeof(T) * size);
		}
		/** Writes an array */
		template <typename T> inline void WriteArray(const std::vector<T> &t) {
			Write(t.size()); // Write the size of the array
			output_stream.write((char*)&t[0], sizeof(T) * t.size());
		}
		
	public:
		FileOutputStream() : open(false) { }
		
		/** Writes an object type */
		template <typename T> inline void Write(const T &t) {
			output_stream.write((char*)&t, sizeof(T));
		}
		
		/** Checks if the stream is open */
		inline bool IsOpen() const {
			return open;
		}
		/** Opens the stream for writing */
		bool Open(const std::string &file) {
			if ( open ) return false;
			output_stream.open(file, std::ios::binary | std::ios::out);
			return (open = output_stream.good());
		}
		/** Closes the stream */
		void Close() {
			if ( open ) {
				output_stream.close();
				open = false;
			}
		}
		
		
		
		/** Writes a byte of information */
		void WriteByte(byte x) {
			Write(x);
		}
		/** Writes a character */
		void WriteChar(char x) {
			Write(x);
		}
		/** Writes a short */
		void WriteShort(short x) {
			Write(x);
		}
		/** Writes an int */
		void WriteInt(int x) {
			Write(x);
		}
		/** Writes a long */
		void WriteLong(long x) {
			Write(x);
		}
		/** Writes a float */
		void WriteFloat(float x) {
			Write(x);
		}
		/** Writes a double */
		void WriteDouble(double x) {
			Write(x);
		}
		/** Writes a string */
		void WriteString(const std::string &string) {
			WriteArray(string.c_str(), string.size());
			WriteChar('\0');
		}
		
		
		static void Wrap(scripting::Script *script);
	};
	
	
	
	/** A file input stream, modeled after Java's DataInputStream class */
	class FileInputStream {
		typedef char byte;
		
		std::ifstream input_stream;
		bool open;
		
		
		template <typename T> T* ReadArray(long *length_out) {
			// Determine the length of the array and its size
			*length_out = ReadLong();
			long num_bytes = sizeof(T) * (*length_out);
			
			// Read the array
			char *read = new char[num_bytes];
			input_stream.read((char*)read, num_bytes);
			
			// Return the array
			return (T*)read;
		}
		
		
		
	public:
		FileInputStream() : open(false) { }
		
		/** Checks if this stream is open */
		inline bool IsOpen() const {
			return open;
		}
		/** Opens the stream for reading */
		bool Open(const std::string &file) {
			if ( open ) return false;
			else {
				input_stream.open(file, std::ios::binary | std::ios::in);
				return (open = input_stream.good());
			}
		}
		/** Closes the stream */
		void Close() {
			if ( open ) {
				input_stream.close();
				open = false;
			}
		}
		
		
		/** Reads an object type */
		template <typename T> T& Read(T *t_out) {
			// Allocate memory for the object
			char read[sizeof(T)];
			
			// Read the object
			input_stream.read((char*)read, sizeof(T));
			
			// Return some stuff
			*t_out = *(T*)read;
			return *t_out;
		}
		
		
		/** Reads a byte of information */
		byte ReadByte() {
			byte b;
			return Read<byte>(&b);
		}
		/** Reads a character */
		char ReadChar() {
			char c;
			return Read<byte>(&c);
		}
		/** Reads a short */
		short ReadShort() {
			short s;
			return Read<short>(&s);
		}
		/** Reads an int */
		int ReadInt() {
			int i;
			return Read<int>(&i);
		}
		/** Reads a long */
		long ReadLong() {
			long l;
			return Read<long>(&l);
		}
		/** Reads a float */
		float ReadFloat() {
			float f;
			return Read<float>(&f);
		}
		/** Reads a double */
		double ReadDouble() {
			double d;
			return Read<double>(&d);
		}
		/** Reads a string */
		std::string ReadString() {
			std::vector<char> chars;
			chars.reserve(64);
			for (int i = 0; i < sizeof(short); ++i) {
				char c = ReadChar();
				chars.push_back(c);
				if ( c == '\0' ) break; // Terminating character
			}
			
			return std::string(chars.begin(), chars.end());
		}
		
		
		static void Wrap(scripting::Script *script);
	};
	
	
	
	
}

#endif /* File_hpp */
