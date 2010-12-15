<?php // $Id: shurly_integration.admin.inc $
/**
 * @file
 * Tools for integrating with the Oxfam Short URL service, oxf.am.
 */

/**
 * Admin form for oxf.am integration.
 */
function shurly_integration_admin_form($form_state) {
  $form = array();
 
  $form['global_account'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global account'),
    '#description' => t('Global account details for integration with oxf.am.'),
  );
  $form['global_account']['oxf_am_do_shurl'] = array(
    '#type' => 'checkbox',
    '#title' => t('Make short URLs for nodes with oxf.am service'),
    '#default_value' => variable_get('oxf_am_do_shurl', TRUE),
  );
  $form['global_account']['oxf_am_site_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Oxf.am site url'),
    '#description' => t('Omit the trailing slash. Drupal will add this.'),
    '#default_value' => variable_get('oxf_am_site_url', 'http://oxf.am'),
    '#disabled' => TRUE,
  );
  $form['global_account']['oxf_am_global_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Oxf.am API key'),
    '#default_value' => variable_get('oxf_am_global_api_key', NULL),
    '#description' => t('This is generated at the user account pages on !oxfam.', array('!oxfam' => l(variable_get('oxf_am_site_url', 'http://oxf.am'), variable_get('oxf_am_site_url', 'http://oxf.am') .'/user'))),
  );
  $form['global_account']['oxf_am_api_service'] = array(
    '#type' => 'select',
    '#title' => t('Oxf.am API service'),
    '#default_value' => variable_get('oxf_am_api_service', ''),
    '#options' => array(
      'txt'  => t('Plain text'),
      'xml'   => t('XML'),
      'php'   => t('PHP serialized array'),
    ),
    '#description' => version_compare(PHP_VERSION, '5.2.0', '>=') ? t('It is advisable that you use the JSON service method, since your version of PHP supports this.') : t('Your current version of PHP is !cversion. If you were using 5.2.0 or greater you could use the superior JSON service method.'),
  );
  if (version_compare(PHP_VERSION, '5.2.0', '>=')) {
    $form['global_account']['oxf_am_api_service']['#options'] = array('json'  => t('JSON')) + $form['global_account']['oxf_am_api_service']['#options'];
    $form['global_account']['oxf_am_api_service']['#default_value'] = variable_get('oxf_am_api_service', 'json');
  }
  $form['node_types'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node types'),
    '#description' => t('Choose the node types that should be integrated with oxf.am for an automatic short URL.'),
  );
  $form['node_types']['oxf_am_node_types'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Allowed node types'),
    '#options' => node_get_types('names'),
    '#default_value' => variable_get('oxf_am_node_types', array()),
  );
  
  return system_settings_form($form); 
}