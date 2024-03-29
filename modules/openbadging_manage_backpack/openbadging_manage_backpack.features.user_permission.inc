<?php
/**
 * @file
 * openbadging_manage_backpack.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function openbadging_manage_backpack_user_default_permissions() {
  $permissions = array();

  // Exported permission: create user_groups achievement.
  $permissions['create user_groups achievement'] = array(
    'name' => 'create user_groups achievement',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: delete any user_groups achievement.
  $permissions['delete any user_groups achievement'] = array(
    'name' => 'delete any user_groups achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: delete own user_groups achievement.
  $permissions['delete own user_groups achievement'] = array(
    'name' => 'delete own user_groups achievement',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: edit any user_groups achievement.
  $permissions['edit any user_groups achievement'] = array(
    'name' => 'edit any user_groups achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: edit own user_groups achievement.
  $permissions['edit own user_groups achievement'] = array(
    'name' => 'edit own user_groups achievement',
    'roles' => array(
      0 => 'authenticated user',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: view user_groups achievement.
  $permissions['view user_groups achievement'] = array(
    'name' => 'view user_groups achievement',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'openbadging',
  );

  return $permissions;
}
