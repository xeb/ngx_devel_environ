/*
 * Copyright (C) 2012 Mark Kockerbeck
 *
 * NOTE: Some small fragments have been copied from ngx_http_udplog_module.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

typedef ngx_addr_t ngx_httplog_addr_t;
typedef struct ngx_http_log_op_s  ngx_http_log_op_t;

typedef struct 
{
    ngx_httplog_addr_t         peer_addr;
    ngx_http_connection_t      *http_connection;
} ngx_http_endpoint_t;

typedef struct 
{
    ngx_http_endpoint_t       *endpoint;
} ngx_httplog_t;

typedef struct 
{
    ngx_array_t                *endpoints;
} ngx_httplog_main_conf_t;



static ngx_int_t ngx_httplog_postconfig(ngx_conf_t *cf);
static char *ngx_httplog_set_log(ngx_conf_t *cf, ngx_command_t *cmd, void *conf);

static ngx_command_t  ngx_httplog_commands[] = {

    { ngx_string("access_httplog"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_HTTP_LIF_CONF
                        |NGX_HTTP_LMT_CONF|NGX_CONF_TAKE1234,
      ngx_httplog_set_log,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },

      ngx_null_command
};

static ngx_http_module_t  ngx_httplog_module_ctx = {
    NULL,                                  /* preconfiguration */
    ngx_httplog_postconfig,                /* postconfiguration */

    NULL, //ngx_http_udplog_create_main_conf,      /* create main configuration */
    NULL,                                  /* init main configuration */

    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */

    NULL, //ngx_http_udplog_create_loc_conf,       /* create location configration */
    NULL, //ngx_http_udplog_merge_loc_conf         /* merge location configration */
};

ngx_module_t  ngx_httplog_module = {
    NGX_MODULE_V1,
    &ngx_httplog_module_ctx,           /* module context */
    ngx_httplog_commands,              /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};

/* Set Log Configuration */
static char * ngx_httplog_set_log(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    return NGX_CONF_OK;
}

/* init endpoint */
static ngx_int_t ngx_httplog_init_endpoint(ngx_conf_t *cf, ngx_http_endpoint_t *endpoint) 
{

    return NGX_OK;
}

/* Main handler */
ngx_int_t ngx_httplog_handler(ngx_http_request_t *r)
{
    return NGX_OK;
}

/* Module postconfig */
static ngx_int_t ngx_httplog_postconfig(ngx_conf_t *cf)
{
    ngx_int_t                     rc;
    ngx_uint_t                    i;
    ngx_http_core_main_conf_t    *cmcf;
    ngx_httplog_main_conf_t  	 *lmcf;
    ngx_http_handler_pt          *h;
    ngx_http_endpoint_t          *e;

 	lmcf = ngx_http_conf_get_module_main_conf(cf, ngx_httplog_module);

    if(lmcf->endpoints != NULL) {
        e = lmcf->endpoints->elts;
        for(i = 0;i < lmcf->endpoints->nelts;i++) {
            rc = ngx_httplog_init_endpoint(cf, e + i);

            if(rc != NGX_OK) {
                return NGX_ERROR;
            }
        }

        cmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_core_module);

        h = ngx_array_push(&cmcf->phases[NGX_HTTP_LOG_PHASE].handlers);
        if (h == NULL) {
            return NGX_ERROR;
        }

        *h = ngx_httplog_handler;
    }

    return NGX_OK;

 }
