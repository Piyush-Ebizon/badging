<?php

/**
 * @file
 * Provide views data and handlers for openbadging.module
 */
/**
 *
 * Includes the ability to create views of just the achievement_unlocks, achievement_total table.
 * @{
 */

/**
 * Implements hook_views_data()
 */
function openbadging_badges_views_data() {
  // Basic table information.
  // ----------------------------------------------------------------

  $data['achievement_unlocks']['table']['group'] = t('Achievement Badges');
  $data['achievement_unlocks']['table']['base'] = array(
      'field' => 'achievement_id',
      'title' => t('All Achievement Badges'),
      'help' => t("Achivements on entity."),
  );
  $data['achievement_unlocks']['table']['entity type'] = 'achievement_unlocks';
//  $data['achievement_unlocks']['table']['default_relationship'] = array(
//      'openbadging' => array(
//          'table' => 'openbadging',
//          'field' => 'achievement_id',
//      ),
//  );
  $data['achievement_totals']['table']['group'] = t('Achievement Users');
  $data['achievement_totals']['table']['base'] = array(
      'field' => 'achievement_id',
      'title' => t('Achievement Totals'),
      'help' => t("Achivements on user Totals."),
  );
  $data['achievement_totals']['table']['entity type'] = 'achievement_totals';
  $data['achievement_totals']['table']['default_relationship'] = array(
      'openbadging' => array(
          'table' => 'openbadging',
          'field' => 'achievement_id',
      ),
  );
  $data['achievement_totals']['achievement_id'] = array(
      'title' => t('Achievement ID'),
      'help' => t('The achievement ID of the field'),
      'relationship' => array(
          'title' => t('Achievement Badge'),
          'help' => t("The Achievement ID of the achievement."),
          'base' => 'openbadging',
          'base field' => 'bid',
          'handler' => 'entity_views_handler_relationship_by_bundle',
          'label' => t('Achievement Badge'),
      ),
      'field' => array(
          'handler' => 'views_handler_field_node',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_node_nid',
          'name field' => 'title', // the field to display in the summary.
          'numeric' => TRUE,
          'validate type' => 'nid',
      ),
  );

  $data['achievement_unlocks']['achievement_id'] = array(
      'title' => t('Achievement ID'),
      'help' => t('The achievement ID of the field'),
      'relationship' => array(
          'title' => t('Achievement Badge'),
          'help' => t("The Achievement ID of the achievement."),
          'base' => 'openbadging',
          'base field' => 'bid',
          'handler' => 'entity_views_handler_relationship_by_bundle',
          'label' => t('Achievement Badge'),
      ),
      'field' => array(
          'handler' => 'views_handler_field_node',
          'click sortable' => TRUE,
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array(
          'handler' => 'views_handler_sort',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
          'name field' => 'title', // the field to display in the summary.
          'numeric' => TRUE,
          'validate type' => 'entity_id',
      ),
  );
  $data['achievement_unlocks']['uid'] = array(
      'title' => t('Achievement uid'),
      'help' => t('If you need more fields than the uid add the achievement: author relationship'),
      'relationship' => array(
          'title' => t('Achievement User'),
          'help' => t("The User ID of the achievement's user."),
          'base' => 'users',
          'base field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Achievement User'),
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
      'field' => array(
          'handler' => 'views_handler_field_user',
      ),
  );
  $data['achievement_totals']['uid'] = array(
      'title' => t('Achievement uid'),
      'help' => t('If you need more fields than the uid add the achievement: author relationship'),
      'relationship' => array(
          'title' => t('Achievement User'),
          'help' => t("The User ID of the achievement's user."),
          'base' => 'users',
          'base field' => 'uid',
          'handler' => 'views_handler_relationship',
          'label' => t('Achievement User'),
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_numeric',
      ),
      'argument' => array(
          'handler' => 'views_handler_argument_numeric',
      ),
      'field' => array(
          'handler' => 'views_handler_field_user',
      ),
  );
  $data['achievement_unlocks']['timestamp'] = array(
      'title' => t('Achievement Timestamp'),
      'help' => t('Date and time of when the earn the achievement.'),
      'field' => array(
          'handler' => 'views_handler_field_achievement_timestamp',
          'click sortable' => TRUE,
      ),
      'sort' => array(
          'handler' => 'views_handler_sort_date',
      ),
      'filter' => array(
          'handler' => 'views_handler_filter_date',
      ),
  );
//  $data['achievement_unlocks']['table']['join'] = array(
//      'profile' => array(
//          'left_field' => 'uid',
//          'field' => 'uid'
//      ),
//      'achievement_totals' => array(
//          'left_field' => 'uid',
//          'field' => 'uid'
//      )
//  );
//  $data['achievement_totals']['unlocks'] = array(
//      'title' => t('Total Achievement'),
//      'help' => t('The number of Achievements a user has.'),
//      'field' => array(
//          'handler' => 'views_handler_field_numeric',
//          'click sortable' => TRUE,
//      ),
//      'filter' => array(
//          'handler' => 'views_handler_filter_numeric',
//      ),
//      'sort' => array(
//          'handler' => 'views_handler_sort',
//      ),
//      'argument' => array(
//          'handler' => 'views_handler_argument',
//      ),
//  );

  return $data;
}

/**
 * Implements hook_views_plugins().
 */
function openbadging_badges_views_plugins() {
  return array(
      'module' => 'openbadging_badges', // This just tells our themes are elsewhere.
      'row' => array(
          'achievements_entity' => array(
              'title' => t('Badge View'),
              'help' => t('Display the badge view.'),
              'handler' => 'views_plugin_row_badge_view',
              'path' => drupal_get_path('module', 'openbadging_badges'), // not necessary for most modules
              'theme' => 'views_view_row_badge_view',
              'base' => array('achievement_unlocks'), // only works with 'node' as base.
              'uses options' => TRUE,
              'type' => 'normal',
              'help topic' => 'style-node',
          ),
      ),
  );
}

/**
 * Template helper for theme_views_view_row_achievement_view
 */
function template_preprocess_views_view_row_badge_view(&$vars) {
  $options = $vars['options'];
  $view = &$vars['view'];
  $plugin = &$view->style_plugin->row_plugin;

//  $comment = $plugin->comments[$vars['row']->{$vars['field_alias']}];
//  $node = $plugin->nodes[$comment->nid];
//  // Put the view on the node so we can retrieve it in the preprocess.
//  $node->view = &$view;
//
//  $build = comment_view_multiple(array($comment->cid => $comment), $node, $plugin->options['view_mode']);
//  // If we're displaying the comments without links, remove them from the
//  // renderable array. There is no way to avoid building them in the first
//  // place (see comment_build_content()).
//  if (empty($options['links'])) {
//    foreach ($build as $cid => &$comment_build) {
//      if (isset($comment_build['links'])) {
//        unset($comment_build['links']);
//      }
//    }
//  }
//  $vars['comment'] = drupal_render($build);
}
