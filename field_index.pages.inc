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

  $form['entity_type'] = array(
      '#type'          => 'select',
      '#title'         => t('Entity type'),
      '#options'       => array(),
      '#default_value' => isset($field_index->entity_type) ? $field_index->entity_type : '',
  );

  $form['bundle'] = array(
      '#type'          => 'select',
      '#title'         => t('Bundle'),
      '#options'       => array(),
      '#default_value' => isset($field_index->bundle) ? $field_index->bundle : '',
  );

//  $form['fields'] = array(
//      '#type'          => 'select',
//      '#title'         => t('Fields'),
//      '#options'       => array(),
//      '#default_value' => isset($field_index->fields) ? $field_index->bundle : '',
//  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array('#type' => 'submit', '#value' => t('Save field index'), '#weight' => 40);

  return $form;
}
