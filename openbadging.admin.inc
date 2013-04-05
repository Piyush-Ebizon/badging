<?php

// $Id openbadging.admin.inc

/**
 * @file
 * Admin settings of for the openbadging module.
 */

/**
 * Generates the task type editing form.
 */
function achievement_types_form($form, &$form_state, $achievement_type, $op = 'edit') {

    if ($op == 'clone') {
        $achievement_type->label .= ' (cloned)';
        $achievement_type->type = '';
    }

    $form['label'] = array(
        '#title' => t('Label'),
        '#type' => 'textfield',
        '#default_value' => $achievement_type->label,
        '#description' => t('The human-readable name of this achievement type.'),
        '#required' => TRUE,
        '#size' => 30,
    );

    // Machine-readable type name.
    $form['type'] = array(
        '#type' => 'machine_name',
        '#default_value' => isset($achievement_type->type) ? $achievement_type->type : '',
        '#maxlength' => 32,
        '#disabled' => $achievement_type->isLocked() && $op != 'clone',
        '#machine_name' => array(
            'exists' => 'openbadging_types',
            'source' => array('label'),
        ),
        '#description' => t('A unique machine-readable name for this achievement type. It must only contain lowercase letters, numbers, and underscores.'),
    );

    $form['description'] = array(
        '#type' => 'textarea',
        '#default_value' => isset($achievement_type->description) ? $achievement_type->description : '',
        '#description' => t('Description about the achievement type.'),
    );

    $form['actions'] = array('#type' => 'actions');
    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save achievement type'),
        '#weight' => 40,
    );

    if (!$achievement_type->isLocked() && $op != 'add' && $op != 'clone') {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete achievement type'),
            '#weight' => 45,
            '#limit_validation_errors' => array(),
            '#submit' => array('achievement_types_form_submit_delete'),
        );
    }
    return $form;
}

/**
 * Submit handler for creating/editing achievement_type.
 */
function achievement_types_form_submit(&$form, &$form_state) {
    $achievement_type = entity_ui_form_submit_build_entity($form, $form_state);
    // Save and go back.
    openbadging_save($achievement_type);

    // Redirect user back to list of achievement types.
    $form_state['redirect'] = 'admin/structure/achievement';
}

/**
 * Function for delete achievement types 
 */
function achievement_types_form_submit_delete(&$form, &$form_state) {
    $form_state['redirect'] = 'admin/structure/achievement/' . $form_state['achievement_types']->type . '/delete';
}

/**
 * Achievement type delete form.
 */
function achievement_types_form_delete_confirm($form, &$form_state, $achievement_type) {
    $form_state['achievement_types'] = $achievement_type;
    // Always provide entity id in the same form key as in the entity edit form.
    $form['achievement_types_id'] = array('#type' => 'value',
        '#value' => entity_id('achievement_types', $achievement_type),
    );
    return confirm_form($form, t('Are you sure you want to delete achievement type %title?', array('%title' => entity_label('achievement_types', $achievement_type))), 'achievement/' . entity_id('achievement_types', $achievement_type), t('This action cannot be undone.'), t('Delete'), t('Cancel')
    );
}

/**
 * Achievement type delete form submit handler.
 */
function achievement_types_form_delete_confirm_submit($form, &$form_state) {
    $achievement_type = $form_state['achievement_types'];
    achievement_types_delete($achievement_type);

    watchdog('achievement_types', '@type: deleted %title.', array('@type' => $achievement_type->type, '%title' => $achievement_type->label));
    drupal_set_message(t('@type %title has been deleted.', array('@type' => $achievement_type->type, '%title' => $achievement_type->label)));

    $form_state['redirect'] = 'admin/structure/achievement';
}

/**
 * Page to select Achievement Type to add new Achievement.
 */
function openbadging_admin_add_page() {
    $items = array();
    foreach (openbadging_types() as $achievement_types_key => $achievement_types) {
        $items[] = l(entity_label('achievement_types', $achievement_types), 'achievement/add/' . $achievement_types_key);
    }
    return array('list' => array('#theme' => 'item_list',
            '#items' => $items,
            '#title' => t('Select type of achievement to create.'),
            ));
}

/**
 * Add new achievement page callback.
 */
function openbadging_add($type) {
    $achievement_types = openbadging_types($type);

    $achievement = entity_create('openbadging', array('type' => $type));
    drupal_set_title(t('Create @name', array('@name' => entity_label('achievement_types', $achievement_types))));

    $output = drupal_get_form('openbadging_form', $achievement);

    return $output;
}

/**
 * Achievement Form.
 */
function openbadging_form($form, &$form_state, $achievement) {
    $form_state['achievement'] = $achievement;

    $form['title'] = array(
        '#type' => 'textfield',
        '#required' => TRUE,
        '#title' => t('Title'),
        '#default_value' => $achievement->title,
    );

    /* $form['description'] = array(
      '#type' => 'textarea',
      '#title' => t('Description'),
      '#default_value' => $achievement->description,
      ); */

    $form['uid'] = array(
        '#type' => 'value',
        '#value' => $achievement->uid,
    );
    field_attach_form('openbadging', $achievement, $form, $form_state);

    $submit = array();
    if (!empty($form['#submit'])) {
        $submit += $form['#submit'];
    }

    $form['actions'] = array(
        '#weight' => 100,
    );

    $form['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Save'),
        '#submit' => $submit + array('openbadging_form_submit'),
    );

    // Show Delete button if we edit achievement.
    $achievement_id = entity_id('openbadging', $achievement);
    if (!empty($achievement_id) && openbadging_access('edit', $achievement)) {
        $form['actions']['delete'] = array(
            '#type' => 'submit',
            '#value' => t('Delete'),
            '#submit' => array('openbadging_form_submit_delete'),
        );
    }

    $form['#validate'][] = 'openbadging_form_validate';

    return $form;
}

/*
 * Implementation of form validation 
 */

function openbadging_form_validate($form, &$form_state) {
    
}

/**
 * Achievement submit handler.
 * @param array $form
 * @param array $form_state
 */
function openbadging_form_submit($form, &$form_state) {
    $achievement = $form_state['achievement'];

    entity_form_submit_build_entity('openbadging', $achievement, $form, $form_state);

    openbadging_save($achievement);

    $achievement_uri = entity_uri('openbadging', $achievement);

    $form_state['redirect'] = $achievement_uri['path'];

    drupal_set_message(t('Achievement %title saved.', array('%title' => entity_label('openbadging', $achievement))));
}

/**
 * function call on deleting achievement entity
 * @param array $form
 * @param array $form_state 
 */
function openbadging_form_submit_delete($form, &$form_state) {
    $achievement = $form_state['achievement'];
    $achievement_uri = entity_uri('openbadging', $achievement);
    $form_state['redirect'] = $achievement_uri['path'] . '/delete';
}

/**
 * Delete confirmation form.
 * @param array $form
 * @param array $form_state
 * @param type $achievement
 * @return array
 */
function openbadging_delete_form($form, &$form_state, $achievement) {
    $form_state['achievement'] = $achievement;
    // Always provide entity id in the same form key as in the entity edit form.
    $form['achievement_type_id'] = array('#type' => 'value',
        '#value' => entity_id('openbadging', $achievement));
    $achievement_uri = entity_uri('openbadging', $achievement);
    return confirm_form($form, t('Are you sure you want to delete achievement %title?', array('%title' => entity_label('openbadging', $achievement))), $achievement_uri['path'], t('This action cannot be undone.'), t('Delete'), t('Cancel')
    );
}

/**
 * Delete form submit handler.
 */
function openbadging_delete_form_submit($form, &$form_state) {
    $achievement = $form_state['achievement'];
    openbadging_delete($achievement);
    drupal_set_message(t('Achievement %title deleted.', array('%title' => entity_label('openbadging', $achievement))));
    $form_state['redirect'] = '<front>';
}

/* * *****changes for admin content tab***** */

/**
 * Menu callback: content administration.
 */
function openbadging_admin_content($form, $form_state) {
    if (isset($form_state['values']['operation']) && $form_state['values']['operation'] == 'delete') {
        return achievement_types_form_delete($form, $form_state, array_filter($form_state['values']['nodes']));
    }
    $form['filter'] = openbadging_filter_form();
    $form['#submit'][] = 'openbadging_filter_form_submit';
    $form['admin'] = achievement_admin_achievements();
    return $form;
}

/**
 * Return form for openbadging administration filters.
 */
function openbadging_filter_form() {
    $session = isset($_SESSION['node_overview_filter']) ? $_SESSION['node_overview_filter'] : array();
    $filters = openbadging_filters();
    $i = 0;
    $form['filters'] = array(
        '#type' => 'fieldset',
        '#title' => t('Show only items where'),
        '#theme' => 'exposed_filters__node',
    );
    foreach ($session as $filter) {
        list($type, $value) = $filter;
        $value = $filters[$type]['options'][$value];
        $t_args = array('%property' => $filters[$type]['title'], '%value' => $value);
        $form['filters']['current'][] = array('#markup' => t('where %property is %value', $t_args));
        if (in_array($type, array('type'))) {
            // Remove the option if it is already being filtered on.
            unset($filters[$type]);
        }
    }

    $form['filters']['status'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('clearfix')),
        '#prefix' => ($i ? '<div class="additional-filters">' . t('and where') . '</div>' : ''),
    );
    $form['filters']['status']['filters'] = array(
        '#type' => 'container',
        '#attributes' => array('class' => array('filters')),
    );
    foreach ($filters as $key => $filter) {
        $form['filters']['status']['filters'][$key] = array(
            '#type' => 'select',
            '#options' => check_plain($filter['options']),
            '#title' => check_plain($filter['title']),
            '#default_value' => '[any]',
        );
    }

    $form['filters']['status']['actions'] = array(
        '#type' => 'actions',
        '#attributes' => array('class' => array('container-inline')),
    );
    $form['filters']['status']['actions']['submit'] = array(
        '#type' => 'submit',
        '#value' => count($session) ? t('Reset') : t('Filter'),
    );
    drupal_add_js('misc/form.js');

    return $form;
}

/**
 * Process result from node administration filter form.
 */
function openbadging_filter_form_submit($form, &$form_state) {
    $filters = openbadging_filters();
    switch ($form_state['values']['op']) {
        case t('Filter'):
            // Apply every filter that has a choice selected other than 'any'.
            foreach ($filters as $filter => $options) {
                if (isset($form_state['values'][$filter]) &&
                        $form_state['values'][$filter] != '[any]') {
                    // Flatten the options array to accommodate 
                    // hierarchical/nested options.
                    $flat_options = form_options_flatten($filters[$filter]['options']);
                    // Only accept valid selections offered on the dropdown, block bad input.
                    if (isset($flat_options[$form_state['values'][$filter]])) {
                        $_SESSION['node_overview_filter'][] = array($filter, $form_state['values'][$filter]);
                    }
                }
            }
            break;
        case t('Reset'):
            $_SESSION['node_overview_filter'] = array();
            break;
    }
}

/**
 * List openbadging administration filters that can be applied.
 */
function openbadging_filters() {
    $filters['type'] = array(
        'title' => t('type'),
        'options' => array(
    '[any]' => t('any'),
        ) + openbadging_type_get_names(),
    );
    return $filters;
}

/**
 * Form builder: Builds the node administration overview.
 */
function achievement_admin_achievements() {
    $admin_access = user_access('administer nodes');
    // Build the 'Update options' form.
    $form['options'] = array(
        '#type' => 'fieldset',
        '#title' => t('Update options'),
        '#attributes' => array('class' => array('container-inline')),
        '#access' => $admin_access,
    );
    $options = array();
    foreach (module_invoke_all('achievement_operations') as $operation => $array) {
        $options[$operation] = $array['label'];
    }
    $form['options']['operation'] = array(
        '#type' => 'select',
        '#title' => t('Operation'),
        '#title_display' => 'invisible',
        '#options' => $options,
        '#default_value' => 'approve',
    );
    $form['options']['submit'] = array(
        '#type' => 'submit',
        '#value' => t('Update'),
        '#validate' => array('achievement_admin_achievements_validate'),
        '#submit' => array('achievement_admin_achievements_submit'),
    );
    // Enable language column if translation module is enabled
    // or if we have any node with language.
    // Build the sortable table header.
    $header = array(
        'title' => array('data' => t('Title'), 'field' => 'n.title'),
        'type' => array('data' => t('Type'), 'field' => 'n.type'),
        'author' => t('Author'),
        'changed' => array('data' => t('Updated'), 
            'field' => 'n.changed', 
            'sort' => 'desc'),
    );
    $header['operations'] = array('data' => t('Operations'));
    $query = db_select('openbadging', 'n')->extend('PagerDefault')->extend('TableSort');
    achievement_build_filter_query($query);
    if (!user_access('bypass node access')) {
        // If the user is able to view their own unpublished nodes, allow them
        // to see these in addition to published nodes. Check that they actually
        // have some unpublished nodes to view before adding the condition.
        if (user_access('view own unpublished content') && $own_unpublished = db_query('SELECT bid FROM {openbadging} WHERE uid = :uid', array(':uid' => $GLOBALS['user']->uid))->fetchCol()) {
            $query
                    ->condition('n.bid', $own_unpublished, 'IN');
        }
    }
    $bids = $query
            ->fields('n', array('bid'))
            ->limit(50)
            ->orderByHeader($header)
            ->execute()
            ->fetchCol();
    $achievements = openbadging_load_multiple($bids);
    // Prepare the list of nodes.
    $destination = drupal_get_destination();
    $options = array();
    foreach ($achievements as $achievement) {
        $account = user_load($achievement->uid, $reset = FALSE);
        $options[$achievement->bid] = array(
            'title' => array(
                'data' => array(
                    '#type' => 'link',
                    '#title' => $achievement->title,
                    '#href' => 'achievement/' . $achievement->bid,
                    '#suffix' => ' ' . theme('mark', array('type' => openbadging_mark($achievement->bid, $achievement->changed))),
                ),
            ),
            'type' => openbadging_type_get_name($achievement),
            'author' => theme('username', array('account' => $account)),
            'changed' => format_date($achievement->changed, 'short'),
        );
        // Build a list of all the accessible operations for the current node.
        $operations = array();
        $operations['edit'] = array(
            'title' => t('edit'),
            'href' => 'achievement/' . $achievement->bid . '/edit',
            'query' => $destination,
        );
        $operations['delete'] = array(
            'title' => t('delete'),
            'href' => 'achievement/' . $achievement->bid . '/delete',
            'query' => $destination,
        );
        $options[$achievement->bid]['operations'] = array();
        if (count($operations) > 1) {
            // Render an unordered list of operations links.
            $options[$achievement->bid]['operations'] = array(
                'data' => array(
                    '#theme' => 'links__node_operations',
                    '#links' => $operations,
                    '#attributes' => array('class' => array('links', 'inline')),
                ),
            );
        } 
        elseif (!empty($operations)) {
            // Render the first and only operation as a link.
            $link = reset($operations);
            $options[$achievement->bid]['operations'] = array(
                'data' => array(
                    '#type' => 'link',
                    '#title' => $link['title'],
                    '#href' => $link['href'],
                    '#options' => array('query' => $link['query']),
                ),
            );
        }
    }
    // Only use a tableselect when the current user is able to perform any
    // operations.
    if ($admin_access) {
        $form['nodes'] = array(
            '#type' => 'tableselect',
            '#header' => $header,
            '#options' => $options,
            '#empty' => t('No content available.'),
        );
    }
    // Otherwise, use a simple table.
    else {
        $form['nodes'] = array(
            '#theme' => 'table',
            '#header' => $header,
            '#rows' => $options,
            '#empty' => t('No content available.'),
        );
    }
    $form['pager'] = array('#markup' => theme('pager'));
    return $form;
}

/**
 * Validate achievement_admin_achievements form submissions.
 * Check if any achievement have been selected to perform the chosen
 */
function achievement_admin_achievements_validate($form, &$form_state) {
    // Error if there are no items to select.
    if (!is_array($form_state['values']['nodes']) || !count(array_filter($form_state['values']['nodes']))) {
        form_set_error('', t('No items selected.'));
    }
}

/**
 * Execute the chosen 'Update option' on the selected achievements.
 */
function achievement_admin_achievements_submit($form, &$form_state) {
    $operations = module_invoke_all('achievement_operations');
    $operation = $operations[$form_state['values']['operation']];
    // Filter out unchecked nodes.
    $achievements = array_filter($form_state['values']['nodes']);
    if ($function = $operation['callback']) {
        // Add in callback arguments if present.
        if (isset($operation['callback arguments'])) {
            $args = array_merge(array($achievements), $operation['callback arguments']);
        } 
        else {
            $args = array($achievements);
        }
        call_user_func_array($function, $args);

        cache_clear_all();
    } 
    else {
        // We need to rebuild the form to go to a second step. For example, to
        // show the confirmation form for the deletion of nodes.
        $form_state['rebuild'] = TRUE;
    }
}

/**
 * Implements hook_achievement_operations().
 */
function openbadging_achievement_operations() {
    $operations = array(
        'delete' => array(
            'label' => t('Delete selected content'),
            'callback' => NULL,
        ),
    );
    return $operations;
}

/**
 * Achievement type delete form.
 */
function achievement_types_form_delete($form, &$form_state, $achievements) {
    $form['nodes'] = array('#prefix' => '<ul>', 
        '#suffix' => '</ul>', 
        '#tree' => TRUE);
    // Array_filter returns only elements with TRUE values.
    foreach ($achievements as $bid => $value) {
        $title = db_query('SELECT title FROM {openbadging} WHERE bid = :bid', array(':bid' => $bid))->fetchField();
        $form['nodes'][$bid] = array(
            '#type' => 'hidden',
            '#value' => $bid,
            '#prefix' => '<li>',
            '#suffix' => check_plain($title) . "</li>\n",
        );
    }
    $form['operation'] = array('#type' => 'hidden', '#value' => 'delete');
    $form['#submit'][] = 'achievement_multiple_delete_submit';
    $confirm_question = format_plural(count($achievements), 'Are you sure you want to delete this item?', 'Are you sure you want to delete these items?');
    return confirm_form($form, $confirm_question, 'admin/content', t('This action cannot be undone.'), t('Delete'), t('Cancel'));
}

/**
 * Achievement type delete multiple submit form.
 */
function achievement_multiple_delete_submit($form, &$form_state) {
    if ($form_state['values']['confirm']) {
        openbadging_delete_multiple(array_keys($form_state['values']['nodes']));
        $count = count($form_state['values']['nodes']);
        watchdog('content', 'Deleted @count posts.', array('@count' => $count));
        drupal_set_message(format_plural($count, 'Deleted 1 post.', 'Deleted @count posts.'));
    }
    $form_state['redirect'] = 'admin/structure/achievement/content';
}

/**
 * Apply filters for openbadging administration filters based on session.
 * @param SelectQueryInterface $query
 * A SelectQuery to which the filters should be applied.
 */
function achievement_build_filter_query(SelectQueryInterface $query) {
    // Build query.
    $filter_data = isset($_SESSION['node_overview_filter']) ? $_SESSION['node_overview_filter'] : array();
    foreach ($filter_data as $index => $filter) {
        list($key, $value) = $filter;
        switch ($key) {
            case 'type':
                $query->condition('n.' . $key, $value);
                break;
        }
    }
}
