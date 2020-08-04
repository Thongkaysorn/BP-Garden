#pragma once

#include "RequestInterface.h"
#include <HTTPClient.h>
#include <WiFiClient.h>

namespace http {
  class GenericEspRequestImpl : public RequestInterface {
  public:
    GenericEspRequestImpl() : RequestInterface() {}

    void setUrl(String url) override {
      _http.begin(this->_client, url);
    }

    void setMethod(Method m) override {
      _method = m;
    }

    void setBody(String body) override {
      this->_body = body;
    }

    void addHeader(String key, String value) override {
      _http.addHeader(key, value);
    }
    
    Response execute() override {
      int httpCode = -1;
      if(this->_method == Method::GET) httpCode = this->_http.sendRequest("GET", this->_body);
      else if(this->_method == Method::POST) httpCode = this->_http.sendRequest("POST", this->_body);
      
      Response response;
      response.statusCode = httpCode;
      
      if(httpCode == 200) {
        response.body = "";//this->_http.getString();
        while(_client.available()) {
          char ch = _client.read();
          response.body += ch;
        }
      }
      else response.body = this->_http.errorToString(httpCode);
      
      return response;
    }

    virtual ~GenericEspRequestImpl() {}

  private:
    Method _method;
    String _body, _url;
    HTTPClient _http;
    WiFiClient _client;
  };
};