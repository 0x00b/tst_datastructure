#ifndef _TST_TRAITS_H_
#define _TST_TRAITS_H_

template<typename T>
struct TstIteratorTraits
{
	typedef typename T::value_type value_type;
};

/*
template<typename T>
struct TstIteratorTraits<T*>
{
	typedef typename T::value_type value_type;
};*/


template<typename TstIter>
typename TstIteratorTraits<TstIter>::value_type*
TstValueType(const TstIter& it)
{
	return static_cast<typename TstIteratorTraits<TstIter>::value_type*>(0);
}

/*
* typetraits
*/
struct tst_falsetype {};
struct tst_truetype {};

template<class T>
struct TstTypeTraits
{
	//	typedef  tst_falsetype this_dummy_member_must_be_first;
	/*
	* 这里我的type_traits命名不是和stl中一样，所以这一个成员定义有没有其实无所谓
	* 按照原来stl中的注释，我理解是这个成员跟编译器有关，如果一个模板的名字是__type_traits。
	* 因为编译器可能会有自己定义的__type_traits。
	*/
	typedef  tst_falsetype has_trivial_defualt_constructor;	//有默认的构造函数
	typedef  tst_falsetype has_trivial_copy_constructor;	//有拷贝构造
	typedef  tst_falsetype has_trivial_assignment_operator;	//有赋值元算符 =
	typedef  tst_falsetype has_trivial_desturctor;			//有析构
	typedef  tst_falsetype is_POD_type;						//POD is Plain Old Data,
															//大概是内置的类型比如int，float
};
template<class T>
struct TstTypeTraits<T*>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};
template<>
struct TstTypeTraits<char>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};
template<>
struct TstTypeTraits<bool>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};
template<>
struct TstTypeTraits<short>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<unsigned short>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<int>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<unsigned int>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<long>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<unsigned long>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<long long>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<unsigned long long>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<float>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<double>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<long double>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<char*>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<unsigned char*>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};


template<>
struct TstTypeTraits<signed char*>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};

template<>
struct TstTypeTraits<const char*>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};


template<>
struct TstTypeTraits<const signed char*>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};
template<>
struct TstTypeTraits<const unsigned char*>
{
	typedef  tst_truetype has_trivial_defualt_constructor;
	typedef  tst_truetype has_trivial_copy_constructor;
	typedef  tst_truetype has_trivial_assignment_operator;
	typedef  tst_truetype has_trivial_desturctor;
	typedef  tst_truetype is_POD_type;
};


#endif
