<?php

/**
 * Field index entity form.
 * @param array $form
 * @param array $form_state
 * @param FieldIndex $field_index
 * @param string $op
 */
function field_index_form($form, &$form_state, $field_index, $op = 'edit') {
  $form += array();

  $form['label'] = array(
      '#type'          => 'textfield',
      '#title'         => t('Label'),
      '#default_value' => isset($field_index->label) ? $field_index->label : '',
      '#description'   => t('The human-readable name of this currency.'),
      '#required'      => TRUE,
      '#size'          => 30,
  );

  // Machine-readable type name.
  $form['name'] = array(
      '#type'          => 'machine_name',
      '#default_value' => isset($field_index->name) ? $field_index->name : '',
      '#maxlength'     => 32,
      '#disabled'      => $field_index->isLocked() && $op !== 'clone',
      '#machine_name'  => array(
          'exists' => 'bella_currency_load',
          'source' => array('label')
      ),
      '#description'   => t('A unique machine-readable name for this currency. It must only contain lowercase letters, numbers, and underscores.'),
  );

  // @TODO: On change, ajax load bundles
  $entity_type_options = array();
  foreach (field_index_controller() as $type_name => $type_info) {
    $entity_type_options[$type_name] = $type_info['label'];
  }

  $form['entity_type'] = array(
      '#type'          => 'select',
      '#title'         => t('Entity type'),
      '#options'       => $entity_type_options,
      '#default_value' => isset($field_index->entity_type) ? $field_index->entity_type : '',
  );

  // @TODO: On change, ajax load fields
  $form['bundle'] = array(
      '#type'          => 'select',
      '#title'         => t('Bundle'),
      '#options'       => array(), // @TODO: Bundle of entity if it's available
      '#default_value' => isset($field_index->bundle) ? $field_index->bundle : '',
  );

  // @TODO: On change, ajax load columns
  $form['field'] = array(
      '#type'          => 'select',
      '#title'         => t('Field'),
      '#options'       => array(), // @TODO: List of fields
      '#default_value' => isset($field_index->field) ? $field_index->field : '',
  );

  $form['column_names'] = array(
      '#type'          => 'select', // @TODO: checkboxes if length is greater then 5
      '#multiple'      => TRUE,
      '#title'         => t('Fields'),
      '#options'       => array(), // @TODO: List columns
      '#default_value' => isset($field_index->column_names) ? $field_index->column_names : array(),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save field index'), '#weight' => 40);

  return $form;
}
