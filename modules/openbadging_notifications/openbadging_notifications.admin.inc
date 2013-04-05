<?php

// $Id achievement_notifications.admin.inc

/**
 * @file
 * Admin settings for achievement notification.
 */


/**
 * Achievement notification mail setup for admin.
 */
function openbadging_notifications_settings() {

    $form['achievement_notification_mail_subject'] = array(
        '#title' => t('Achievement Notification Subject'),
        '#type' => 'textfield',
        '#default_value' => variable_get('achievement_notification_mail_subject', 'Congratulations %first_name! You received a badge from %issuer_name'),
    );

    $form['achievement_notification_mail_before_login_body'] = array(
        '#title' => t('Achievement Notification Text Before Login'),
        '#type' => 'textarea',
        '#default_value' => variable_get('achievement_notification_mail_before_login_body', 'Congratulations %first_name,
      
You have been awarded with %badge_name by %issuer_name

Issuer details: 
Origin - %issuer_origin
Name - %issuer_name
Contact - %issuer_contact

Badge details:
Version - %badge_name
Name - %badge_version
Description - %badge_description

Go to %one-time-login-url to view your badge. You can change the privacy setting of your badge from My Backpack. Go to My Backpack, create a group, assign badges to group and then change its privacy. 

Best Wishes,
Society for Science & The Public Badge System'),
        '#description' => t('Edit the e-mail messages sent to users when badge award to user.'),
    );

    $form['achievement_notification_mail_after_login_body'] = array(
        '#title' => t('Achievement Notification Text After Login'),
        '#type' => 'textarea',
        '#default_value' => variable_get('achievement_notification_mail_after_login_body', 'Congratulations %first_name,
You have been awarded with %badge_name by %issuer_name

Issuer details: 
Origin - %issuer_origin
Name - %issuer_name
Contact - %issuer_contact

Badge details:
Version - %badge_name
Name - %badge_version
Description - %badge_description

Go to %login_url to view your badge. You can change the privacy setting of your badge from My Backpack. Go to My Backpack, create a group, assign badges to group and then change its privacy. 

Best Wishes,
Society for Science & The Public Badge System'),
        '#description' => t('Edit the e-mail messages sent to users when badge award to user.'),
    );
    return system_settings_form($form);
}
