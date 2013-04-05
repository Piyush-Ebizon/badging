<?php

//$Id openbadging-my-backpack-view.tpl.php

/**
 * User group view for badges on user's manage backpack which is created by user.
 * Only user can see these groups and user can set badge & group privacy.
 * 
 * Variables:
 * "Variables['view']" variable to show view result.
 *    
 */
?>
<div class="my-backpack-badges-view">
    <div class="my-backpack-badges-content-field">
        <?php
        if (empty($variables['view'])) {
            print t('If you have badges you have been awarded, you can group them here and change their privacy.');
        } else {
            foreach ($variables['view'] as $key => $value) {
                ?>

                <?php
                global $base_url;
                $check_status_privacy = user_group_status_check($value->bid);
                if ($check_status_privacy == 1) {
                    $image_url_unlock = $base_url . '/' . drupal_get_path('module', 'openbadging_manage_backpack') . '/images/private.png';
                } else {
                    $image_url_unlock = $base_url . '/' . drupal_get_path('module', 'openbadging_manage_backpack') . '/images/public.png';
                }
                $criteria_link_unlock = 'achievement/' . $value->bid . '/edit';
                print '<h3>' . $value->openbadging_title . l(t('<img src="' . render($image_url_unlock) . '"/>'), $criteria_link_unlock, array('html' => TRUE)) . '</h3>';
                ?>
                <div class="my-backpack-edit-delete-view">
                <?php
                global $base_url;
                $criteria_link_edit = 'achievement/' . $value->bid . '/edit';
                $image_url_edit = $base_url . '/' . drupal_get_path('module', 'openbadging_manage_backpack') . '/images/edit.png';
                print l(t('<img src="' . ($image_url_edit) . '"/>'), $criteria_link_edit, array('html' => TRUE));
                ?> 
                </div>
                <div class="my-backpack-badge-image">
                    <?php
                    global $base_url;
                    foreach ($value->field_field_badge_entity_reference_1 as $key1 => $value1) {
                        $img_url = $value1['raw']['entity']->field_badge_entity_unlock_image['und'][0]['uri'];

                        $new_path = explode('.png', $img_url);
                        $img_url = $new_path[0] . '-' . $value->_field_data['bid']['entity']->uid . '.png';

                        $img = theme('image_style', array('style_name' => '110_110', 'path' => $img_url, 'alt' => NULL, 'title' => NULL));
                        $title = get_badge_title_mozila_send($value1['raw']['entity']->bid);
                        print l($img, $base_url . '/achievement/' . $value1['raw']['entity']->bid, array('html' => TRUE));
                    }
                    ?>           
                </div>
                <?php }
            }
            ?>
    </div>       
</div>
