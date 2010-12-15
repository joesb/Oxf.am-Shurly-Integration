<?php // $Id: shurly_integration.theme.inc $
/**
 * @file
 * Theme functions for Oxf.am integration tools.
 */

/**
 * Theme function for Tweet This block.
 *
 * @return $output String of content output.
 */
function theme_shurly_tweet_this($node) {
  $path = drupal_get_path('module', 'shurly_integration') .'/images/tweet-this.png';
  $alt = $title = t('Tweet this');
  $status = array('status' => $node->title .' | '. variable_get('site_name', '') .' '. $node->shurl['short_url']);
  $image = theme('image', $path, $alt, $title, array('class' => 'img tweet-this tweet-this-img', 'id' => 'oxf-am-tweet-this-img'));
  $output = l($image, 'http://twitter.com/', array('html' => TRUE, 'attributes' => array('title' => $title, 'target' => '_blank', 'class' => 'tweet-this tweet-this-anchor', 'id' => 'oxf-am-tweet-this'), 'query' => $status));
  return $output;
}

function theme_shurly_permalink($node) {
  $output = t('<strong>Permalink:</strong> !url', array('!url' => l($node->shurl['short_url'], $node->shurl['short_url'])));
  return $output;
}
