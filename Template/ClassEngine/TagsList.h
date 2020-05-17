#pragma once

/**
 * \brief This class keeps tree-like structure that consists of pair TAG : VALUE + LIST of TagList-s\n
 * It is equivalent to XML without attributes. This is very fast and lightweight version of XML/JSON/PB\n
 * 
 */
class  TagsList
{
public:
	TagsList();
	~TagsList();
	TagsList(const char* QuoteName);
	//new/delete are using pool, so this is fast
	void operator delete(void* ptr, size_t size);
	void* operator new(size_t size);

	///convert tag value to int
	int to_int () const;
	///get value of the tag
	const char* to_string() const;
	///last saved/loaded file with tags
	static comms::cStr LastTagFile;

	///convert string to the tags structure
	int GetTagsFromString(const char* XMLSource);
	///convert tags structure to the string
	int PutTagsIntoString(comms::cStr* Source,int shift=0);
	///read tags from file
	bool ReadTagsFromFile(const char* FilePath);
	///save tags to file
	void WriteTagsToFile(const char* FilePath);

	///assign int value to the tag value
	void Assign(int v);
	///assign string value to the tag
	void Assign(const char* s);

	///Add already allocated tag to the tags list within this tag
	int AddSubTag(TagsList* SubQ);
	///Add new tag to the tags list within this tag
	int AddSubTag(const char* quotename, const char* body);
	///Add new tag with integer value  to the tags list within this tag
	int AddSubTag(const char* quotename, int body);
	///Get sub-tag by index
	TagsList* GetSubTag(int Index);
	///Get sub-tag by name
	TagsList* GetSubTag(const char* SubQuoteName);
	///Get amount of sub-tags
	int GetSubTagsCount();

	///Remove sub-tag by index
	void RemoveSubTag(int idx);
	///Remove and return tag by index. The return value will not be destroyed, you should do it later by yourself.
	TagsList* RemoveAndGetSubTag(int idx);

	///returns this tag name
	const char* GetTagName();
	///set name for the current tag. If this tag was already used somewhere, the memory will not be allocated for the name.
	void SetTagName(const char* Name);
	///free all memory associated with this tag
	void FreeTag();
	///copy 
	void operator = (TagsList& src);
	///This function returns constant location for the input string. Even if the input string will be destroyed later, the return value will be kept till the program termination.
	static const char* GetConstantLocation(const char* str);
	static int& GetConstantLocationValueRef(const char* str);
	///This function returns constant location for the input sub - string (max length = Len). Even if the input string will be destroyed later, the return value will be kept till the program termination.
	static const char* GetConstantSubstringLocation(const char* str, int Len, int** value = nullptr);
private:
	const char* _tagname;
	const char* _tag(const char* tag);
    comms::cList<TagsList*> SubTags;
	comms::cStr TagBody;
};
inline TagsList* new_TagsList(){
	TagsList* x=(TagsList*)POOL.Allocate(sizeof(TagsList));	
	memset(x,0,sizeof(TagsList));
	return x;
}
inline TagsList* new_TagsList(const char* s){
	TagsList* x=new_TagsList();
	x->SetTagName(s);
	return x;
}
inline void delete_TagsList(TagsList* x){
	x->FreeTag();
	POOL.Free((BYTE*)x,sizeof(TagsList));
} 
inline void TagsList::operator delete(void* ptr, size_t size) {
	delete_TagsList((TagsList*)ptr);
}
inline void* TagsList::operator new(size_t size) {
	return new_TagsList();
}
