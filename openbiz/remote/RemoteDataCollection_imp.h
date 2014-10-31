//
//  RemoteDataCollection_imp.h
//  Openbiz-RestModel
//
//  Created by Jixian Wang on 14-10-11.
//  Copyright (c) 2014年 openbiz. All rights reserved.
//

#ifndef Openbiz_RestModel_RemoteDataCollection_imp_h
#define Openbiz_RestModel_RemoteDataCollection_imp_h

template<typename T>
openbiz::remote::DataCollection<T>::DataCollection(const std::string &url,
                                                   const std::string &cacheName,
                                                   const bool usingRemotePaging):
_baseUrl(url),
_usingRemotePaging(usingRemotePaging),
openbiz::data::DataCollection<T>(cacheName){
    
};

template<typename T>
openbiz::remote::DataCollection<T>::~DataCollection(){
    
}

template<typename T>
const std::string openbiz::remote::DataCollection<T>::getUrl() const throw()
{
    if(!_usingRemotePaging) return _baseUrl;
    
    std::string formattedURL(this->_baseUrl);
    formattedURL += "?per_page="+ std::to_string(this->_pageSize)+
                    "&page="+std::to_string(this->_pageId);
    if(!this->_keyword.empty())
    {
        formattedURL += "?keyword="+ this->_keyword;
    }
    return formattedURL;
};

template<typename T>
void openbiz::remote::DataCollection<T>::fetch()
{
    RestClient::response r = RestClient::get(getUrl());
    switch(r.code)
    {
        case -1:
            if(this->isCacheEnabled())
            {
                //try to load cached data
                openbiz::data::DataCollection<T>::fetch();
            }else{
                //if collection has no cache enabled,
                throw openbiz::exception::NetworkConnectionException(r);
            }
            break;
        case 200:
            if(_usingRemotePaging){
                Json::Reader reader;
                Json::Value data;
                bool result = reader.parse(r.body,data);
                if(!result){
                    throw openbiz::exception::DataFormatInvalidException(r.body);
                }
                openbiz::data::DataCollection<T>::_totalRecords = data[0]["total_entries"].asInt();
                openbiz::data::DataCollection<T>::_totalPages   = data[0]["total_pages"].asInt();
                openbiz::data::DataCollection<T>::_pageSize     = data[0]["per_page"].asInt();
                openbiz::data::DataCollection<T>::_pageId       = data[0]["page"].asInt();
                openbiz::data::DataCollection<T>::parse(data[1]);
            }else{
                openbiz::data::DataCollection<T>::parse(r.body);
            }
            openbiz::data::DataCollection<T>::save();
            break;
        case 204:
        default:
            break;
    }
    return  ;
};


#endif
