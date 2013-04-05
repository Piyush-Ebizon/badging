<?php

/**
 * @file
 * Class AchievementEntityController define for the openbadging module.
 */


class AchievementEntityController extends EntityAPIController {

    public function create(array $values = array()) {
        global $user;
        $values += array(
            'title' => '',
            'description' => '',
            'created' => REQUEST_TIME,
            'changed' => REQUEST_TIME,
            'uid' => $user->uid,
        );
        return parent::create($values);
    }

    /**
     * Overriding the buldContent function to add entity specific fields
     */
    public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
        //$wrapper = entity_metadata_wrapper('openbadging', $entity);
        //$content['author'] = array('#markup' => t('Created by: !author', array('!author' => $wrapper->uid->name->value(array('sanitize' => TRUE)))));

        return parent::buildContent($entity, $view_mode, $langcode, $content);
    }

}

class AchievementTypesController extends EntityAPIControllerExportable {

    public function create(array $values = array()) {
        $values += array(
            'label' => '',
            'description' => '',
        );
        return parent::create($values);
    }

    /**
     * Save Achievement Type.
     */
    public function save($entity, DatabaseTransaction $transaction = NULL) {
        parent::save($entity, $transaction);
        // Rebuild menu registry. We do not call menu_rebuild directly, but set
        // variable that indicates rebuild in the end.
        // @see http://drupal.org/node/1399618
        variable_set('menu_rebuild_needed', TRUE);
    }

}

/**
 * UI controller for Achievement Type.
 */
class AchievementTypesEntityController extends EntityDefaultUIController {

    /**
     * Overrides hook_menu() defaults.
     */
    public function hook_menu() {
        $items = parent::hook_menu();
        $items[$this->path]['description'] = 'Manage achievement types.';
        return $items;
    }

}

/**
 * achievement class.
 */
class AchievementEntity extends Entity {

    protected function defaultLabel() {
        return $this->title;
    }

    protected function defaultUri() {
        return array('path' => 'achievement/' . $this->identifier());
    }

}

/**
 * Achievement Type class.
 */
class AchievementTypes extends Entity {

    public $type;
    public $label;
    public $weight = 0;

    public function __construct($values = array()) {
        parent::__construct($values, 'achievement_types');
    }

    function isLocked() {
        return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
    }

}
