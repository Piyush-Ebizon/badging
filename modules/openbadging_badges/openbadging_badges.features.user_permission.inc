<?php
/**
 * @file
 * openbadging_badges.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function openbadging_badges_user_default_permissions() {
  $permissions = array();

  // Exported permission: administer openbadging.
  $permissions['administer openbadging'] = array(
    'name' => 'administer openbadging',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: administer openbadging types.
  $permissions['administer openbadging types'] = array(
    'name' => 'administer openbadging types',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: create badges achievement.
  $permissions['create badges achievement'] = array(
    'name' => 'create badges achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: delete any badges achievement.
  $permissions['delete any badges achievement'] = array(
    'name' => 'delete any badges achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: delete own badges achievement.
  $permissions['delete own badges achievement'] = array(
    'name' => 'delete own badges achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: edit any badges achievement.
  $permissions['edit any badges achievement'] = array(
    'name' => 'edit any badges achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: edit own badges achievement.
  $permissions['edit own badges achievement'] = array(
    'name' => 'edit own badges achievement',
    'roles' => array(
      0 => 'administrator',
    ),
    'module' => 'openbadging',
  );

  // Exported permission: view badges achievement.
  $permissions['view badges achievement'] = array(
    'name' => 'view badges achievement',
    'roles' => array(
      0 => 'anonymous user',
      1 => 'authenticated user',
    ),
    'module' => 'openbadging',
  );

  return $permissions;
}
