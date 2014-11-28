<?php

class FieldIndex extends Entity {

  public $id;
  public $name;
  public $label;
  public $published;
  public $status;
  public $entity_type;
  public $bundle;
  public $field;
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
