<?php

/**
 * @file
 * openbadging_view function for the openbadging module.
 */

/**
 * Sets up content to show an individual model
 * @todo - get rid of drupal_set_title();
 */
function openbadging_view($achievement, $view_mode = 'full') {
    $controller = entity_get_controller('openbadging');
    $content = $controller->view(array($achievement->bid => $achievement));
    return $content;
}
