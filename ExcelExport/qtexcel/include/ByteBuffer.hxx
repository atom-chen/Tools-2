#ifndef _BYTEBUFFER_H
#define _BYTEBUFFER_H

#include "Common.hxx"
#include "ByteConverter.hxx"
#include "Error.hxx"
#include "SystemEndian.hxx"
#include "Platform.hxx"
#include "System.hxx"

BEGIN_NAMESPACE

class ByteBufferException
{
    public:
        ByteBufferException(bool _add, size_t _pos, size_t _esize, size_t _size)
            : add(_add), pos(_pos), esize(_esize), size(_size)
        {
            PrintPosError();
        }

        void PrintPosError() const;
    private:
        bool add;
        size_t pos;
        size_t esize;
        size_t size;
};

template<class T>
struct Unused
{
    Unused() {}
};

class ByteBuffer
{
	protected:
		SysEndian m_sysEndian;

    public:
        const static size_t DEFAULT_SIZE = 1 * 1024;	// 1024 Ĭ�� 4k

        // constructor
        ByteBuffer(): _rpos(0), _wpos(0)
        {
			m_sysEndian = eSys_LITTLE_ENDIAN;		// Ĭ����С��
            _storage.reserve(DEFAULT_SIZE);
        }

        // constructor
        ByteBuffer(size_t res): _rpos(0), _wpos(0)
        {
			m_sysEndian = eSys_LITTLE_ENDIAN;		// Ĭ����С��
            _storage.reserve(res);
        }

        // copy constructor
        ByteBuffer(const ByteBuffer& buf): _rpos(buf._rpos), _wpos(buf._wpos), _storage(buf._storage) 
		{
			m_sysEndian = eSys_LITTLE_ENDIAN;		// Ĭ����С��
		}

        void clear()
        {
            _storage.clear();
            _rpos = _wpos = 0;
        }

		// �����ֵһ����ϵͳ��С��һ����
        template <typename T>
		void put(size_t pos, T value)
        {
			if (System::getSingletonPtr()->isEndianDiffFromSys(m_sysEndian))
			{
				EndianConvert(value);
			}
            put(pos, (uint8*)&value, sizeof(value));
        }

		ByteBuffer& writeUnsignedInt8(uint8 value)
        {
            append<uint8>(value);
            return *this;
        }

		ByteBuffer& writeUnsignedInt16(uint16 value)
        {
            append<uint16>(value);
            return *this;
        }

		ByteBuffer& writeUnsignedInt32(uint32 value)
        {
            append<uint32>(value);
            return *this;
        }

		ByteBuffer& writeUnsignedInt64(uint64 value)
        {
            append<uint64>(value);
            return *this;
        }

        // signed as in 2e complement
		ByteBuffer& writeInt8(int8 value)
        {
            append<int8>(value);
            return *this;
        }

		ByteBuffer& writeInt16(int16 value)
        {
            append<int16>(value);
            return *this;
        }

		ByteBuffer& writeInt32(int32 value)
        {
            append<int32>(value);
            return *this;
        }

		ByteBuffer& writeInt64(int64 value)
        {
            append<int64>(value);
            return *this;
        }

        // floating points
		ByteBuffer& writeFloat(float value)
        {
            append<float>(value);
            return *this;
        }

		ByteBuffer& writeDouble(double value)
        {
            append<double>(value);
            return *this;
        }

		// д�� UTF-8 �ַ����������ַ������� '\0' ���Լ����õ������
		ByteBuffer& writeMultiByte(const std::string& value, size_t len)
        {
			if (len > value.length())
			{
				append((uint8 const*)value.c_str(), value.length());
				append(len - value.length());
			}
			else
			{
				append((uint8 const*)value.c_str(), len);
			}
            // append((uint8)0);
            return *this;
        }

		ByteBuffer& writeMultiByte(const char* str, size_t len)
        {
            //append((uint8 const*)str, str ? strlen(str) : 0);
            // append((uint8)0);
			if (str)
			{
				size_t charLen = strlen(str) / sizeof(char);
				if (len > charLen)
				{
					append(str, charLen);
					append(len - charLen);
				}
				else
				{
					append(str, len);
				}
			}
			else
			{
				append(len);
			}
            return *this;
        }

		ByteBuffer& readBoolean(bool& value)
        {
            value = read<char>() > 0 ? true : false;
            return *this;
        }

		ByteBuffer& readUnsigneduint8(uint8& value)
        {
            value = read<uint8>();
            return *this;
        }

		ByteBuffer& readUnsigneduint16(uint16& value)
        {
            value = read<uint16>();
            return *this;
        }

		ByteBuffer& readUnsignedInt32(uint32& value)
        {
            value = read<uint32>();
            return *this;
        }

		ByteBuffer& readUnsignedInt64(uint64& value)
        {
            value = read<uint64>();
            return *this;
        }

        // signed as in 2e complement
		ByteBuffer& readInt8(int8& value)
        {
            value = read<int8>();
            return *this;
        }

		ByteBuffer& readInt16(int16& value)
        {
            value = read<int16>();
            return *this;
        }

		ByteBuffer& readInt32(int32& value)
        {
            value = read<int32>();
            return *this;
        }

		ByteBuffer& readInt64(int64& value)
        {
            value = read<int64>();
            return *this;
        }

		ByteBuffer& readFloat(float& value)
        {
            value = read<float>();
            return *this;
        }

		ByteBuffer& readDouble(double& value)
        {
            value = read<double>();
            return *this;
        }

		ByteBuffer& readMultiByte(std::string& value, size_t len)
        {
            //value.clear();
            //while (rpos() < size())                         // prevent crash at wrong string format in packet
            //{
            //    char c = read<char>();
            //    if (c == 0)
            //        break;
            //    value += c;
            //}

			value.clear();
			if (len)		// �����Ϊ 0 ���Ͷ�ȡָ������
			{
				size_t readNum = 0;	// �Ѿ���ȡ������
				while (rpos() < size() && readNum < len)                         // prevent crash at wrong string format in packet
				{
					char c = read<char>();
					value += c;
					++readNum;
				}
			}
			else				// ���Ϊ 0 ����һֱ��ȡ��ֱ��������һ�� '\0'
			{
				while (rpos() < size())                         // prevent crash at wrong string format in packet
				{
					char c = read<char>();
					if (c == 0)
					    break;
					value += c;
				}
			}

            return *this;
        }

        template<class T>
		ByteBuffer& readUnused(Unused<T> const&)
        {
            read_skip<T>();
            return *this;
        }

        uint8 operator[](size_t pos) const
        {
            return read<uint8>(pos);
        }

        size_t rpos() const { return _rpos; }

        size_t rpos(size_t rpos_)
        {
            _rpos = rpos_;
            return _rpos;
        }

        size_t wpos() const { return _wpos; }

        size_t wpos(size_t wpos_)
        {
            _wpos = wpos_;
            return _wpos;
        }

		// ������������
        template<typename T>
        void read_skip() { read_skip(sizeof(T)); }

		// ���ݴ�С����
        void read_skip(size_t skip)
        {
            if (_rpos + skip > size())
                throw ByteBufferException(false, _rpos, skip, size());
            _rpos += skip;
        }

		template<typename T>
		void write_skip() { write_skip(sizeof(T)); }

		// ���ݴ�С����
		void write_skip(size_t skip)
		{
			append(skip);
		}

        template <typename T>
		T read()
        {
            T r = read<T>(_rpos);
            _rpos += sizeof(T);
            return r;
        }

		// ��ȡ������һ���Ǻ�ϵͳ��С��һ����
        template <typename T>
		T read(size_t pos) const
        {
            if (pos + sizeof(T) > size())
                throw ByteBufferException(false, pos, sizeof(T), size());
            T val = *((T const*)&_storage[pos]);
			if (System::getSingletonPtr()->isEndianDiffFromSys(m_sysEndian))
			{
				EndianConvert(val);
			}
            return val;
        }

        void read(uint8* dest, size_t len)
        {
            if (_rpos  + len > size())
                throw ByteBufferException(false, _rpos, len, size());
            memcpy(dest, &_storage[_rpos], len);
            _rpos += len;
        }

        const uint8* contents() const { return &_storage[0]; }

        size_t size() const { return _storage.size(); }
        bool empty() const { return _storage.empty(); }

        void resize(size_t newsize)
        {
            _storage.resize(newsize);
            _rpos = 0;
            _wpos = size();
        }

        void reserve(size_t ressize)
        {
            if (ressize > size())
                _storage.reserve(ressize);
        }

		// ��������
        void append(const std::string& str)
        {
            append((uint8 const*)str.c_str(), str.size() + 1);
        }

        void append(const char* src, size_t cnt)
        {
            return append((const uint8*)src, cnt);
        }

        template<class T>
		void append(const T* src, size_t cnt)
        {
            return append((const uint8*)src, cnt * sizeof(T));
        }

        void append(const uint8* src, size_t cnt)
        {
            if (!cnt)
                return;

			assert(size() < 10000000);

            if (_storage.size() < _wpos + cnt)
                _storage.resize(_wpos + cnt);
            memcpy(&_storage[_wpos], src, cnt);
            _wpos += cnt;
        }

		// �����ƶ�дָ�룬�����������
		void append(size_t cnt)
		{
			if (!cnt)
				return;

			assert(size() < 10000000);

			if (_storage.size() < _wpos + cnt)
				_storage.resize(_wpos + cnt);
			_wpos += cnt;
		}

        void append(const ByteBuffer& buffer)
        {
            if (buffer.wpos())
                append(buffer.contents(), buffer.wpos());
        }

        void put(size_t pos, const uint8* src, size_t cnt)
        {
            if (pos + cnt > size())
                throw ByteBufferException(true, pos, cnt, size());
            memcpy(&_storage[pos], src, cnt);
        }

        void print_storage() const;
        void textlike() const;
        void hexlike() const;
		void writeFile(FILE* file);

    private:
		// ��ӵ�һ���Ǻ�ϵͳ��С����ͬ��
        // limited for internal use because can "append" any unexpected type (like pointer and etc) with hard detection problem
        template <typename T>
		void append(T value)
        {
			if (System::getSingletonPtr()->isEndianDiffFromSys(m_sysEndian))
			{
				EndianConvert(value);
			}
            append((uint8*)&value, sizeof(value));
        }

    protected:
		size_t _rpos;		// ��ȡλ��
		size_t _wpos;		// д��λ��
        std::vector<uint8> _storage;		// �洢�ռ�
};

template <typename T>
inline ByteBuffer& operator<<(ByteBuffer& b, std::vector<T> const& v)
{
    b << (uint32)v.size();
    for (typename std::vector<T>::iterator i = v.begin(); i != v.end(); ++i)
    {
        b << *i;
    }
    return b;
}

template <typename T>
inline ByteBuffer& operator>>(ByteBuffer& b, std::vector<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while (vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename T>
inline ByteBuffer& operator<<(ByteBuffer& b, std::list<T> const& v)
{
    b << (uint32)v.size();
    for (typename std::list<T>::iterator i = v.begin(); i != v.end(); ++i)
    {
        b << *i;
    }
    return b;
}

template <typename T>
inline ByteBuffer& operator>>(ByteBuffer& b, std::list<T>& v)
{
    uint32 vsize;
    b >> vsize;
    v.clear();
    while (vsize--)
    {
        T t;
        b >> t;
        v.push_back(t);
    }
    return b;
}

template <typename K, typename V>
inline ByteBuffer& operator<<(ByteBuffer& b, std::map<K, V>& m)
{
    b << (uint32)m.size();
    for (typename std::map<K, V>::iterator i = m.begin(); i != m.end(); ++i)
    {
        b << i->first << i->second;
    }
    return b;
}

template <typename K, typename V>
inline ByteBuffer& operator>>(ByteBuffer& b, std::map<K, V>& m)
{
    uint32 msize;
    b >> msize;
    m.clear();
    while (msize--)
    {
        K k;
        V v;
        b >> k >> v;
        m.insert(make_pair(k, v));
    }
    return b;
}

template<>
inline void ByteBuffer::read_skip<char*>()
{
    std::string temp;
    //*this >> temp;
	this->readMultiByte(temp, 0);
}

template<>
inline void ByteBuffer::read_skip<char const*>()
{
    read_skip<char*>();
}

template<>
inline void ByteBuffer::read_skip<std::string>()
{
    read_skip<char*>();
}

END_NAMESPACE

#endif