<?php // $Id: shurly_integration.inc $
/**
 * @file
 * Helper functions for integrating with the Oxfam Short URL service, oxf.am.
 */
 
/**
 * Get JSON data from short URL service.
 *
 * @return Decoded JSON data as object.
 */
function shurly_integration_shurl_get_json($long_url) {
  $url = shurly_integration_shurl_prepare_url($long_url);

  $result = drupal_http_request($url);
  if ($result->code == 200) {
    $data = json_decode($result->data);
    watchdog('shurly_integration', 'Created a short URL for !long_url and received data with request !url.', array('!long_url' => $long_url, '!url' => $url));
    return $data;
  }
  else {
    watchdog('shurly_integration', 'Could not retrieve short url data with request !url. Error: !error.', array('!url' => $url, '!error' => print_r($result, TRUE)));
  }
  return;
}

/**
 * Get Text data from short URL service.
 *
 * @return Text data as object.
 */
function shurly_integration_shurl_get_text($long_url) {
  $url = shurly_integration_shurl_prepare_url($long_url);
  
  $result = drupal_http_request($url);
  if ($result->code == 200) {
    $data = new stdClass;
    $data->longUrl = $long_url;
    $data->shortUrl = $result->data;
    return $data;
  }
  else {
    watchdog('shurly_integration', 'Could not retrieve short url data with request !url. Error: !error.', array('!url' => $url, '!error' => print_r($result, TRUE)));
  }
  return;
}

/**
 * Get XML data from short URL service.
 *
 * @return XML data as object.
 */
function shurly_integration_shurl_get_xml($long_url) {
  $url = shurly_integration_shurl_prepare_url($long_url);

  $result = drupal_http_request($url);
  if ($result->code == 200) {
    $data = simplexml_load_string($result->data);
    return $data;
  }
  else {
    watchdog('shurly_integration', 'Could not retrieve short url data with request !url. Error: !error.', array('!url' => $url, '!error' => print_r($result, TRUE)));
  }
  return;
}

/**
 * Get PHP data from short URL service.
 *
 * @return PHP data as object.
 */
function shurly_integration_shurl_get_php($long_url) {
  $url = shurly_integration_shurl_prepare_url($long_url);

  $result = drupal_http_request($url);
  if ($result->code == 200) {
    $data = unserialize($result->data);
    return $data;
  }
  else {
    watchdog('shurly_integration', 'Could not retrieve short url data with request !url. Error: !error.', array('!url' => $url, '!error' => print_r($result, TRUE)));
  }
  return;
}

function shurly_integration_shurl_prepare_url($long_url) {
  $query = array('longUrl' => $long_url);
  
  global $user;
  if ($user->oxf_am_api_key) {
    $query['apiKey'] = $user->oxf_am_api_key;
  }
  elseif (variable_get('oxf_am_global_api_key', NULL)) {
    $query['apiKey'] = variable_get('oxf_am_global_api_key', NULL);
  }
  $query['format'] = variable_get('oxf_am_api_service', 'json');
  
  $url = url(variable_get('oxf_am_site_url', 'http://oxf.am') .'/shurly/api/shorten', array('query' => $query));

  return $url;
}