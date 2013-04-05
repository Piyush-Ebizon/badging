<?php
/**
 * @file
 * openbadging_issuer.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function openbadging_issuer_user_default_permissions() {
  $permissions = array();

  // Exported permission: create issuer_information achievement.
  $permissions['create issuer_information achievement'] = array(
    'name' => 'create issuer_information achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: delete any issuer_information achievement.
  $permissions['delete any issuer_information achievement'] = array(
    'name' => 'delete any issuer_information achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: delete own issuer_information achievement.
  $permissions['delete own issuer_information achievement'] = array(
    'name' => 'delete own issuer_information achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: edit any issuer_information achievement.
  $permissions['edit any issuer_information achievement'] = array(
    'name' => 'edit any issuer_information achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: edit own issuer_information achievement.
  $permissions['edit own issuer_information achievement'] = array(
    'name' => 'edit own issuer_information achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: view issuer_information achievement.
  $permissions['view issuer_information achievement'] = array(
    'name' => 'view issuer_information achievement',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'openbadging',
  );

  return $permissions;
}
