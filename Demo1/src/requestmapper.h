/**
  @file
  @author Stefan Frings
*/

#ifndef REQUESTMAPPER_H
#define REQUESTMAPPER_H

#include <HttpRequestHandler.hpp>

using namespace QtWebApp;

/**
  The request mapper dispatches incoming HTTP requests to controller classes
  depending on the requested path.
*/

class RequestMapper : public HttpRequestHandler {
    Q_OBJECT
    Q_DISABLE_COPY( RequestMapper )
public:

    /**
      Constructor.
      @param parent Parent object
    */
    RequestMapper( QObject* parent = nullptr );

    /**
      Destructor.
    */
    ~RequestMapper();

    /**
      Dispatch incoming HTTP requests to different controllers depending on the URL.
      @param request The received HTTP request
      @param response Must be used to return the response
    */
    void service( HttpRequest& request, HttpResponse& response );
};

#endif // REQUESTMAPPER_H
