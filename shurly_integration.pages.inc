<?php // $Id: shurly_integration.admin.inc $
/**
 * @file
 * Tools for integrating with the Oxfam Short URL service, oxf.am.
 */

function shurly_integration_user_settings($account) {

  $output = '';
  $output .= drupal_get_form('shurly_integration_user_settings_form', $account);

  return $output;
}

/**
 * User oxf.am account form.
 */
function shurly_integration_user_settings_form($form_state, $account = array()) {
  $form = array();
  $form['user_account'] = array(
    '#type' => 'fieldset',
    '#title' => t('My oxf.am account'),
    '#description' => t('API key details for integration with oxf.am.'),
  );
  $form['user_account']['oxf_am_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Oxf.am API key'),
    '#default_value' => $account->oxf_am_api_key,
    '#description' => t('This is generated at your user account page on !oxfam.', array('!oxfam' => l(variable_get('oxf_am_site_url', 'http://oxf.am'), variable_get('oxf_am_site_url', 'http://oxf.am') .'/user'))),
  );
  $form['user_account']['account_delete'] = array(
    '#title' => t('Delete API key'),
    '#description' => t('Delete this API key from your account.'),
    '#type' => 'checkbox',
    '#default_value' => FALSE,
  );
  $form['user_account']['account_uid'] = array(
    '#type' => 'hidden',
    '#value' => $account->uid,
  );
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * Submit handler for user oxf.am account form.
 */
function shurly_integration_user_settings_form_submit($form, &$form_state) {
  $values = $form_state['values'];
  $account = array(
    'uid' => $values['account_uid'],
    'api_key' => $values['oxf_am_api_key'],
  );
  if (!empty($values['account_delete'])) {
    shurly_integration_oxfam_account_delete($account);
    drupal_set_message('Oxf.am account API key deleted successfully.');
  }
  else {
    shurly_integration_oxfam_account_set($account);
    drupal_set_message('Oxf.am account API key saved successfully.');
  }
}