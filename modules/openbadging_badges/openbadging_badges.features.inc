<?php
/**
 * @file
 * achievement_badges.features.inc
 */

/**
 * Implements hook_default_achievement_types().
 */
function openbadging_badges_default_achievement_types() {
  $items = array();
  $items['badges'] = entity_import('achievement_types', '{
    "type" : "badges",
    "label" : "Badges",
    "weight" : 0,
    "description" : "Add badges",
    "rdf_mapping" : []
  }');
  return $items;
}

/**
 * Implements hook_views_api().
 */
function openbadging_badges_views_api() {
  return array("version" => "3.0");
}
