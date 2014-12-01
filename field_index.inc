<?php

class FieldIndex extends Entity {

  public $id;
  public $name;
  public $label;
  public $published;
  public $status;
  public $entity_type;
  public $bundle;
  public $field_name;
  public $column_names;

  /**
   * Returns whether the quiz type is locked, thus may not be deleted or renamed.
   *
   * Quiz types provided in code are automatically treated as locked, as well
   * as any fixed quiz type.
   */
  public function isLocked() {
    return isset($this->status) && empty($this->is_new) && (($this->status & ENTITY_IN_CODE) || ($this->status & ENTITY_FIXED));
  }

}

class FieldIndexController extends EntityAPIControllerExportable {

  /**
   * Get entity types which support fields, use SQL storage
   */
  public function getEntityTypes() {
    $info = array();

    foreach (entity_get_info() as $type_name => $entity_info) {
      if (empty($entity_info['fieldable'])) {
        continue;
      }

      if ($this->isSQLEntityType($type_name)) {
        $info[$type_name] = $entity_info;
      }
    }

    return $info;
  }

  protected function isSQLEntityType($type_name) {
    foreach (field_info_instances($type_name) as $field_instances) {
      if (!empty($field_instances)) {
        foreach (array_keys($field_instances) as $field_name) {
          $field_info = field_info_field($field_name);
          if ('field_sql_storage' === $field_info['storage']['module']) {
            return TRUE;
          }
        }
      }
    }
    return FALSE;
  }

}
