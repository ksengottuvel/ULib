// Reminder: Modify typemap.dat to customize the header file generated by wsdl2h
/* csp.h
   Generated by wsdl2h 1.2.6c from csp.wsdl and typemap.dat
   2006-05-15 15:28:05 GMT
   Copyright (C) 2001-2005 Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL or Genivia's license for commercial use.
*/

/* NOTE:

 - Compile this file with soapcpp2 to complete the code generation process.
 - Use soapcpp2 option -I to specify paths for #import
   To build with STL, 'stlvector.h' is imported from 'import' dir in package.
 - Use wsdl2h options -c and -s to generate pure C code or C++ code without STL.
 - Use 'typemap.dat' to control schema namespace bindings and type mappings.
   It is strongly recommended to customize the names of the namespace prefixes
   generated by wsdl2h. To do so, modify the prefix bindings in the Namespaces
   section below and add the modified lines to 'typemap.dat' to rerun wsdl2h.
 - Use Doxygen (www.doxygen.org) to browse this file.
 - Use wsdl2h option -l to view the software license terms.

*/

/******************************************************************************\
 *                                                                            *
 * csp                                                                        *
 *                                                                            *
\******************************************************************************/

//gsoapopt cw

/******************************************************************************\
 *                                                                            *
 * Import                                                                     *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Schema Namespaces                                                          *
 *                                                                            *
\******************************************************************************/

// This service uses SOAP 1.2 namespaces:
//gsoap SOAP-ENV schema namespace:	http://www.w3.org/2003/05/soap-envelope
//gsoap SOAP-ENC schema namespace:	http://www.w3.org/2003/05/soap-encoding

/* NOTE:

It is strongly recommended to customize the names of the namespace prefixes
generated by wsdl2h. To do so, modify the prefix bindings below and add the
modified lines to typemap.dat to rerun wsdl2h:

ns = "csp"

*/

//gsoap ns    schema namespace:	csp
//gsoap ns    schema form:	unqualified

/******************************************************************************\
 *                                                                            *
 * Schema Types                                                               *
 *                                                                            *
\******************************************************************************/




/// Element "csp":CSP-LIST-CA of complexType.

/// "csp":CSP-LIST-CA is a complexType.
struct _ns__CSP_LIST_CA
{
};


/// Element "csp":CSP-LIST-CAResponse of complexType.

/// "csp":CSP-LIST-CAResponse is a complexType.
struct _ns__CSP_LIST_CAResponse
{
/// Element response of type xs:string.
    char*                                response                       1;	///< Required element.
};


/// Element "csp":CSP-CA of complexType.

/// "csp":CSP-CA is a complexType.
struct _ns__CSP_CA
{
/// Element dir of type xs:string.
    char*                                dir                            1;	///< Required element.
/// Element days of type xs:unsignedInt.
    unsigned int                         days                           1;	///< Required element.
/// Element cnf of type xs:string.
    char*                                cnf                            0;	///< Nullable pointer.
};


/// Element "csp":CSP-CAResponse of complexType.

/// "csp":CSP-CAResponse is a complexType.
struct _ns__CSP_CAResponse
{
/// Element response of type xs:string.
    char*                                response                       1;	///< Required element.
};


/// Element "csp":CSP-SIGN-P10 of complexType.

/// "csp":CSP-SIGN-P10 is a complexType.
struct _ns__CSP_SIGN_P10
{
/// Element ca of type xs:string.
    char*                                ca                             1;	///< Required element.
/// Element policy of type xs:string.
    char*                                policy                         1;	///< Required element.
/// Element pkcs10 of type xs:string.
    char*                                pkcs10                         1;	///< Required element.
};


/// Element "csp":CSP-SIGN-P10Response of complexType.

/// "csp":CSP-SIGN-P10Response is a complexType.
struct _ns__CSP_SIGN_P10Response
{
/// Element response of type xs:string.
    char*                                response                       1;	///< Required element.
};


/// Element "csp":CSP-SIGN-SPACK of complexType.

/// "csp":CSP-SIGN-SPACK is a complexType.
struct _ns__CSP_SIGN_SPACK
{
/// Element ca of type xs:string.
    char*                                ca                             1;	///< Required element.
/// Element policy of type xs:string.
    char*                                policy                         1;	///< Required element.
/// Element spack of type xs:string.
    char*                                spack                          1;	///< Required element.
};


/// Element "csp":CSP-SIGN-SPACKResponse of complexType.

/// "csp":CSP-SIGN-SPACKResponse is a complexType.
struct _ns__CSP_SIGN_SPACKResponse
{
/// Element response of type xs:string.
    char*                                response                       1;	///< Required element.
};


/// Element "csp":CSP-LIST-CERTS of complexType.

/// "csp":CSP-LIST-CERTS is a complexType.
struct _ns__CSP_LIST_CERTS
{
/// Element ca of type xs:string.
    char*                                ca                             1;	///< Required element.
/// Element compress of type xs:unsignedInt.
    unsigned int                         compress                       1;	///< Required element.
};


/// Element "csp":CSP-LIST-CERTSResponse of complexType.

/// "csp":CSP-LIST-CERTSResponse is a complexType.
struct _ns__CSP_LIST_CERTSResponse
{
/// Element response of type xs:string.
    char*                                response                       1;	///< Required element.
};


/// Element "csp":CSP-REMOVE-CERT of complexType.

/// "csp":CSP-REMOVE-CERT is a complexType.
struct _ns__CSP_REMOVE_CERT
{
/// Element ca of type xs:string.
    char*                                ca                             1;	///< Required element.
/// Element serial of type xs:string.
    char*                                serial                         1;	///< Required element.
};


/// Element "csp":CSP-REMOVE-CERTResponse of complexType.

/// "csp":CSP-REMOVE-CERTResponse is a complexType.
struct _ns__CSP_REMOVE_CERTResponse
{
/// Element response of type xs:string.
    char*                                response                       1;	///< Required element.
};


/// Element "csp":CSP-ZERO-CERTS of complexType.

/// "csp":CSP-ZERO-CERTS is a complexType.
struct _ns__CSP_ZERO_CERTS
{
/// Element ca of type xs:string.
    char*                                ca                             1;	///< Required element.
};


/// Element "csp":CSP-ZERO-CERTSResponse of complexType.

/// "csp":CSP-ZERO-CERTSResponse is a complexType.
struct _ns__CSP_ZERO_CERTSResponse
{
/// Element response of type xs:string.
    char*                                response                       1;	///< Required element.
};

/******************************************************************************\
 *                                                                            *
 * Services                                                                   *
 *                                                                            *
\******************************************************************************/


//gsoap ns   service name:	CSP 
//gsoap ns   service type:	CSPPortType 
//gsoap ns   service port:	http://10.30.1.131:4433/ 
//gsoap ns   service namespace:	csp 
//gsoap ns   service transport:	http://schemas.xmlsoap.org/soap/http 

/** @mainpage CSP Definitions

@section CSP_bindings Bindings
  - @ref CSP

*/

/**

@page CSP Binding "CSP"

@section CSP_service Service Documentation "CSP"
gSOAP 2.7.6c generated service definition

@section CSP_operations Operations of Binding  "CSP"
  - @ref __ns__CSP_LIST_CA
  - @ref __ns__CSP_CA
  - @ref __ns__CSP_SIGN_P10
  - @ref __ns__CSP_SIGN_SPACK
  - @ref __ns__CSP_LIST_CERTS
  - @ref __ns__CSP_REMOVE_CERT
  - @ref __ns__CSP_ZERO_CERTS

@section CSP_ports Endpoints of Binding  "CSP"
  - http://10.30.1.131:4433/

*/

/******************************************************************************\
 *                                                                            *
 * CSP                                                                        *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * __ns__CSP_LIST_CA                                                          *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns__CSP_LIST_CA" of service binding "CSP"

/**

Operation details:

Service definition of function ns__CSP_LIST_CA
  - SOAP document/literal style

C stub function (defined in soapClient.c[pp]):
@code
  int soap_call___ns__CSP_LIST_CA(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct _ns__CSP_LIST_CA*            ns__CSP_LIST_CA,
    // response parameters:
    struct _ns__CSP_LIST_CAResponse*    ns__CSP_LIST_CAResponse
  );
@endcode

*/

//gsoap ns   service method-style:	CSP_LIST_CA document
//gsoap ns   service method-encoding:	CSP_LIST_CA literal
int __ns__CSP_LIST_CA(
    struct _ns__CSP_LIST_CA*            ns__CSP_LIST_CA,
    struct _ns__CSP_LIST_CAResponse*    ns__CSP_LIST_CAResponse ///< response parameter
);

/******************************************************************************\
 *                                                                            *
 * __ns__CSP_CA                                                               *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns__CSP_CA" of service binding "CSP"

/**

Operation details:

Service definition of function ns__CSP_CA
  - SOAP document/literal style

C stub function (defined in soapClient.c[pp]):
@code
  int soap_call___ns__CSP_CA(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct _ns__CSP_CA*                 ns__CSP_CA,
    // response parameters:
    struct _ns__CSP_CAResponse*         ns__CSP_CAResponse
  );
@endcode

*/

//gsoap ns   service method-style:	CSP_CA document
//gsoap ns   service method-encoding:	CSP_CA literal
int __ns__CSP_CA(
    struct _ns__CSP_CA*                 ns__CSP_CA,
    struct _ns__CSP_CAResponse*         ns__CSP_CAResponse ///< response parameter
);

/******************************************************************************\
 *                                                                            *
 * __ns__CSP_SIGN_P10                                                         *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns__CSP_SIGN_P10" of service binding "CSP"

/**

Operation details:

Service definition of function ns__CSP_SIGN_P10
  - SOAP document/literal style

C stub function (defined in soapClient.c[pp]):
@code
  int soap_call___ns__CSP_SIGN_P10(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct _ns__CSP_SIGN_P10*           ns__CSP_SIGN_P10,
    // response parameters:
    struct _ns__CSP_SIGN_P10Response*   ns__CSP_SIGN_P10Response
  );
@endcode

*/

//gsoap ns   service method-style:	CSP_SIGN_P10 document
//gsoap ns   service method-encoding:	CSP_SIGN_P10 literal
int __ns__CSP_SIGN_P10(
    struct _ns__CSP_SIGN_P10*           ns__CSP_SIGN_P10,
    struct _ns__CSP_SIGN_P10Response*   ns__CSP_SIGN_P10Response ///< response parameter
);

/******************************************************************************\
 *                                                                            *
 * __ns__CSP_SIGN_SPACK                                                       *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns__CSP_SIGN_SPACK" of service binding "CSP"

/**

Operation details:

Service definition of function ns__CSP_SIGN_SPACK
  - SOAP document/literal style

C stub function (defined in soapClient.c[pp]):
@code
  int soap_call___ns__CSP_SIGN_SPACK(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct _ns__CSP_SIGN_SPACK*         ns__CSP_SIGN_SPACK,
    // response parameters:
    struct _ns__CSP_SIGN_SPACKResponse* ns__CSP_SIGN_SPACKResponse
  );
@endcode

*/

//gsoap ns   service method-style:	CSP_SIGN_SPACK document
//gsoap ns   service method-encoding:	CSP_SIGN_SPACK literal
int __ns__CSP_SIGN_SPACK(
    struct _ns__CSP_SIGN_SPACK*         ns__CSP_SIGN_SPACK,
    struct _ns__CSP_SIGN_SPACKResponse* ns__CSP_SIGN_SPACKResponse ///< response parameter
);

/******************************************************************************\
 *                                                                            *
 * __ns__CSP_LIST_CERTS                                                       *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns__CSP_LIST_CERTS" of service binding "CSP"

/**

Operation details:

Service definition of function ns__CSP_LIST_CERTS
  - SOAP document/literal style

C stub function (defined in soapClient.c[pp]):
@code
  int soap_call___ns__CSP_LIST_CERTS(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct _ns__CSP_LIST_CERTS*         ns__CSP_LIST_CERTS,
    // response parameters:
    struct _ns__CSP_LIST_CERTSResponse* ns__CSP_LIST_CERTSResponse
  );
@endcode

*/

//gsoap ns   service method-style:	CSP_LIST_CERTS document
//gsoap ns   service method-encoding:	CSP_LIST_CERTS literal
int __ns__CSP_LIST_CERTS(
    struct _ns__CSP_LIST_CERTS*         ns__CSP_LIST_CERTS,
    struct _ns__CSP_LIST_CERTSResponse* ns__CSP_LIST_CERTSResponse ///< response parameter
);

/******************************************************************************\
 *                                                                            *
 * __ns__CSP_REMOVE_CERT                                                      *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns__CSP_REMOVE_CERT" of service binding "CSP"

/**

Operation details:

Service definition of function ns__CSP_REMOVE_CERT
  - SOAP document/literal style

C stub function (defined in soapClient.c[pp]):
@code
  int soap_call___ns__CSP_REMOVE_CERT(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct _ns__CSP_REMOVE_CERT*        ns__CSP_REMOVE_CERT,
    // response parameters:
    struct _ns__CSP_REMOVE_CERTResponse* ns__CSP_REMOVE_CERTResponse
  );
@endcode

*/

//gsoap ns   service method-style:	CSP_REMOVE_CERT document
//gsoap ns   service method-encoding:	CSP_REMOVE_CERT literal
int __ns__CSP_REMOVE_CERT(
    struct _ns__CSP_REMOVE_CERT*        ns__CSP_REMOVE_CERT,
    struct _ns__CSP_REMOVE_CERTResponse* ns__CSP_REMOVE_CERTResponse ///< response parameter
);

/******************************************************************************\
 *                                                                            *
 * __ns__CSP_ZERO_CERTS                                                       *
 *                                                                            *
\******************************************************************************/


/// Operation "__ns__CSP_ZERO_CERTS" of service binding "CSP"

/**

Operation details:

Service definition of function ns__CSP_ZERO_CERTS
  - SOAP document/literal style

C stub function (defined in soapClient.c[pp]):
@code
  int soap_call___ns__CSP_ZERO_CERTS(struct soap *soap,
    NULL, // char *endpoint = NULL selects default endpoint for this operation
    NULL, // char *action = NULL selects default action for this operation
    // request parameters:
    struct _ns__CSP_ZERO_CERTS*         ns__CSP_ZERO_CERTS,
    // response parameters:
    struct _ns__CSP_ZERO_CERTSResponse* ns__CSP_ZERO_CERTSResponse
  );
@endcode

*/

//gsoap ns   service method-style:	CSP_ZERO_CERTS document
//gsoap ns   service method-encoding:	CSP_ZERO_CERTS literal
int __ns__CSP_ZERO_CERTS(
    struct _ns__CSP_ZERO_CERTS*         ns__CSP_ZERO_CERTS,
    struct _ns__CSP_ZERO_CERTSResponse* ns__CSP_ZERO_CERTSResponse ///< response parameter
);

/* End of csp.h */
