#pragma once
//================================================================================================================//
struct constantTagKeeper {
	char* str;
	int Value;
	constantTagKeeper* next;
};
const char* TagsList::GetConstantLocation(const char* str) {
	return GetConstantSubstringLocation(str, 1000000);
}
int& TagsList::GetConstantLocationValueRef(const char* str) {
	int* value = nullptr;
	GetConstantSubstringLocation(str, 1000000, &value);
	return *value;
}
inline const char* TagsList::GetConstantSubstringLocation(const char* str, int Len, int** value) {
	unsigned int s = 0;
	const int tabsize = 32768;
	int i = 0;
	for (i = 0; str[i] && i<Len; i++)s += (s + (unsigned int)(str[i])) & (tabsize - 1);
	Len = i;
	s &= tabsize - 1;
	static int totalcount = 0;
	static constantTagKeeper* table = nullptr;
	if (!table) {
		table = new constantTagKeeper[tabsize];
		memset(table, 0, sizeof(constantTagKeeper) * tabsize);
	}
	constantTagKeeper* itm = table + s;
	while (itm->str) {
		if (!strncmp(itm->str, str, Len)) {
			if (value)* value = &itm->Value;
			return itm->str;
		}
		if (itm->next)itm = itm->next;
		else break;
	}
	constantTagKeeper* itm2 = itm->str ? new constantTagKeeper : itm;
	itm2->next = nullptr;
	itm2->str = new char[Len + 1];
	if (itm != itm2) {
		itm->next = itm2;
	}
	strncpy_s(itm2->str, Len + 1, str, Len);
	itm2->str[Len] = 0;
	itm2->Value = -1;
	if (value)* value = &itm2->Value;
	totalcount++;
	return itm2->str;
}

const char* TagsList::_tag(const char* tag) {
	return GetConstantLocation(tag);
}

TagsList::TagsList() {
	_tagname = "";
}
TagsList::TagsList(const char* QN)
{
	_tagname = _tag(QN);
}
TagsList::~TagsList()
{
	FreeTag();
}
int TagsList::to_int() const
{
	int rez=0;
	if(TagBody.Length())
	{
		rez=atoi(TagBody.ToCharPtr());
	}
	return rez;
}
void TagsList::RemoveSubTag(int idx){
	delete_TagsList(SubTags[idx]);
    SubTags.RemoveAt( idx, 1 );
}
TagsList* TagsList::RemoveAndGetSubTag(int idx){
	TagsList* x=SubTags[idx];
	SubTags[idx]=NULL;
    SubTags.RemoveAt( idx, 1 );
	return x;
}
const char* TagsList::to_string() const 
{
	return TagBody.ToCharPtr();
}
static bool xml_err=true;
comms::cStr TagsList::LastTagFile;
void PrintXMLError(const char* XML){
	if(xml_err){
		comms::cStr tmp;
		tmp=comms::cStr::Format("Probably XML file [%s] is corrupted.\nPlease delete it manually. Press and keep CTRL to skip errors and delete corrupted XML files automatically.\n",TagsList::LastTagFile.ToCharPtr());
		size_t L=strlen(XML);
		if(L<400){
			tmp += XML;
		}
		else {
			size_t L1 = 200;
			while (L1 < L && L1 < 290 && XML[L1] != 10 && XML[L1] != 13)L1++;
			tmp.Append(XML, 0, (int)L1);
			tmp += "\n........\n";
			L1 = L - 200;
			while (L1 > 0 && L - L1 < 290 && XML[L1] != 10 && XML[L1] != 13)L1--;
			tmp += XML + L1;
		}
		MessageBox(NULL,tmp.ToCharPtr(),"XML Error!",0);
	}
	xml_err=false;
}




int TagsList::GetTagsFromString(const char* XML)
{
	if(XML&&XML[0])
	{
		int pos=0;
		_tagname = "";
        const char* fr = strstr( XML, "<" );
        // comment can be one by one!
        for ( ;; ) {
            static const char* const  waitStart = "<!--";
            static const int  waitStartL = 4;
            static const char* const  waitEnd = "-->";
            static const int  waitEndL = 3;
			const bool  same = fr ? (strncmp(fr, waitStart, waitStartL) == 0) : false;
            if ( same ) {
                // next comment
                for ( const char* frEnd = fr + waitStartL; *frEnd != '\0'; ++frEnd ) {
                    const bool  same = (strncmp( frEnd, waitEnd, waitEndL ) == 0);
                    if ( same ) {
                        fr = frEnd + waitEndL;
                        fr = strstr( fr, "<" );
                        break;
                    }
                }
            }
            else {
                // last comment
                break;
            }
        } // for

        // parse data
		const char* en=NULL;
		if(fr&&*(fr+1)!='/')
		{
			en=strstr(fr,">");
			if(en)
			{
				size_t sz=en-fr;
				const char* _TagName = fr + 1;
				size_t qL = sz - 1;
				if(qL > 0 && _TagName[qL-1]=='/'){
					TagsList* tmp=new_TagsList();
					qL--;				
					tmp->_tagname = GetConstantSubstringLocation(_TagName, (int)qL);
					SubTags.Add(tmp);
					return (int)sz+1;
				}
				else {
					_tagname = GetConstantSubstringLocation(_TagName, (int)qL);					
					size_t Lt = qL;
					while (true)
					{
						//en=strstr(fr+pos,">");
						const char* nm = strstr(en + 1 + pos, "<");
						if (nm)
						{
							size_t ds = nm - en - pos + 1;
							bool havedata = false;
							const char* ffr = NULL;
							const char* ffl = NULL;
							for (int i = 1; i < (ds - 1); i++)
							{
								if (en[i] != 10 && en[i] != 13 && en[i] != 32 && en[i] != 9)
								{
									havedata = true;
									if (!ffr)
										ffr = &en[i];
									ffl = &en[i];
								}
							}
							if (havedata)
							{
								size_t r = ffl - ffr;
								TagBody.Copy(ffr, 0, (int)r + 1);
							}
							if (*(nm + 1) == '/')
							{
								if (!strncmp(nm + 2, _tagname, Lt))
								{
									//OK
									const char* lp = strstr(nm + 2, ">");
									if (lp)
									{
										if (TagBody.ToCharPtr()[0])
										{
											TagBody.Replace("&lt", "<");
											TagBody.Replace("&gt", ">");
										}
										return int(lp - XML + 1);
									}
									else
										return -1;
								}
								else {
									PrintXMLError(XML);
									return -1;
								}
							}
							else
							{
								TagsList* tmp = new_TagsList();
								SubTags.Add(tmp);
								int p = tmp->GetTagsFromString(en + 1 + pos);
								if (p == -1) {
									PrintXMLError(XML);
									return -1;
								}
								else {
									pos += p;
								}
							}
						}
						else {
							return -1;
						}
					}
				}
			}else 
				return -1;
		}else 
			return -1;
	}
	if(TagBody.ToCharPtr()[0])
	{
		TagBody.Replace("&lt","<");
		TagBody.Replace("&gt",">");
	}
	return 0;
}
int TagsList::PutTagsIntoString(comms::cStr* Source,int shift)
{
	int j;
	comms::cStr tempBody;
	for (j = 0; j < shift; j++, Source->Append(" "));
	Source->Append("<");
	Source->Append(_tagname);Source->Append(">");
	int n=SubTags.GetAmount();
	if(n)Source->Append("\n");
	if(TagBody.Length())
	{
		if(n)for(j=0;j<(shift+1);j++,Source->Append(" "));
		tempBody=TagBody;
		tempBody.Replace("<","&lt");
		tempBody.Replace(">","&gt");
		Source->Append(tempBody);
		if(n)Source->Append("\n");
	}
	for(int i=0;i<n;i++)
		if(SubTags[i])
			SubTags[i]->PutTagsIntoString(Source,shift+1);
	if(n){for(j=0;j<shift;j++,Source->Append(" "));}
	Source->Append("</");Source->Append(_tagname);Source->Append(">\n");
	return 0;
}
bool TagsList::ReadTagsFromFile(const char* FilePath)
{
	LastTagFile=FilePath;
	comms::cStr XMLSource;
	StrFromFile(XMLSource,FilePath);
	if(XMLSource.Length() == 0)
		return false;
	int l=GetTagsFromString(XMLSource.ToCharPtr());
	if(l==-1){
#ifdef USE_CIO
		Log.Message("XML Load Error! XML: %s", FilePath);
		if(_CTRL()){
			comms::cIO::RemoveFile(FilePath);
		}
#endif
		return false;
	}
	LastTagFile="unknown";
	return true;
}
void TagsList::WriteTagsToFile(const char* FilePath)
{
	comms::cStr XMLSource;
	PutTagsIntoString(&XMLSource);
	StrToFile(XMLSource, FilePath);
}
void TagsList::Assign(int v)
{
	TagBody.Clear();
	TagBody += v;
}
void TagsList::Assign(const char* s)
{
	TagBody = s;
}
int TagsList::AddSubTag(TagsList* SubQ)
{
	SubTags.Add(SubQ);
	return SubTags.GetAmount();
}
int TagsList::AddSubTag(const char* quotename, const char* body)
{
	SubTags.Add(new_TagsList(quotename));
	SubTags[SubTags.GetAmount()-1]->Assign(body);
	return SubTags.GetAmount();
}
int TagsList::AddSubTag(const char* quotename, int body)
{
	SubTags.Add(new_TagsList(quotename));
	SubTags[SubTags.GetAmount()-1]->Assign(body);
	return SubTags.GetAmount();
}
TagsList* TagsList::GetSubTag(int Index)
{
	TagsList* rez=NULL;
	if(Index<SubTags.GetAmount())
		return (SubTags[Index]);
	return rez;
}
TagsList* TagsList::GetSubTag(const char* SubQuoteName)
{
	int n=SubTags.GetAmount();
	for(int i=0;i<n;i++)
		if(SubTags[i])
			if(!strcmp(SubQuoteName,SubTags[i]->GetTagName()))
				return (SubTags[i]);
	return NULL;
}
int TagsList::GetSubTagsCount()
{
	return SubTags.GetAmount();
}
const char* TagsList::GetTagName()
{
	return _tagname;
}
void TagsList::SetTagName(const char* Name){
	_tagname = _tag(Name);
}
void TagsList::FreeTag()
{
	_tagname = "";
	TagBody.Free();
	int n=SubTags.GetAmount();
	for(int i=0;i<n;i++){		
		if(SubTags[i]){			
			delete_TagsList(SubTags[i]);
			SubTags[i]=NULL;
		}
	}
	SubTags.Free();
}
void TagsList::operator = (TagsList& src) {
	FreeTag();
	_tagname = src._tagname;
	TagBody = src.TagBody;
	for (int i = 0; i < src.SubTags.Count(); i++) {
		TagsList* x = new TagsList;
		*x = *src.SubTags[i];
		AddSubTag(x);
	}
}