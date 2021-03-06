<?php

/**
 * @file
 * Holds views_plugin_style_chart class which implements the chart plugin.
 */

define('VIEWS_PIVOT_MODE_MULTI_VALUE_HORICONTAL', 0);
define('VIEWS_PIVOT_MODE_MULTI_VALUE_VERTICAL', 1);

define('VIEWS_PIVOT_HEADER_KEY', 'views_key_header');

class views_plugin_style_pivot extends views_plugin_style_table {

  /**
   * Set default options.
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['pivot_col'] = array('default' => array());
    $options['pivot_row'] = array('default' => array());
    $options['pivot_mode_multi_values'] = array('default' => VIEWS_PIVOT_MODE_MULTI_VALUE_HORICONTAL);
    return $options;
  }

  /**
   * Options form.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $columns = $this->sanitize_columns($this->options['columns']);
    $form['#theme'] = 'views_ui_style_plugin_pivot';

    $default_pivot_col = empty($this->options['pivot_col']) ?
      array_pop(array_keys($columns)) :
      $this->options['pivot_col'];
    $default_pivot_row = empty($this->options['pivot_row']) ?
      array_shift(array_keys($columns)) :
      $this->options['pivot_row'];

    foreach ($columns as $field => $column) {
      $safe = str_replace(array('][', '_', ' '), '-', $field);
      // the $id of the column for dependency checking.
      $id = 'edit-style-options-columns-' . $safe;

      $radio_id = drupal_html_id('edit-pivot-row-' . $field);
      $form['info'][$field]['pivot_row'] = array(
        '#type' => 'radio',
        '#return_value' => $field,
        '#parents' => array('style_options', 'pivot_row'),
        '#id' => $radio_id,
        '#attributes' => array('id' => $radio_id),
        '#default_value' => $default_pivot_row,
        '#dependency' => array($id => array($field)),
        '#required' => TRUE,
      );
      $form['info'][$field]['pivot_row_extra'] = array(
        '#type' => 'checkbox',
        '#default_value' => !empty($this->options['info'][$field]['pivot_row_extra']),
        '#dependency' => array($id => array($field)),
      );
      $radio_id = drupal_html_id('edit-pivot-col-' . $field);
      $form['info'][$field]['pivot_col'] = array(
        '#type' => 'radio',
        '#return_value' => $field,
        '#parents' => array('style_options', 'pivot_col'),
        '#id' => $radio_id,
        '#attributes' => array('id' => $radio_id),
        '#default_value' => $default_pivot_col,
        '#dependency' => array($id => array($field)),
        '#required' => TRUE,
      );
    }

    $form['pivot_mode_multi_values'] = array(
      '#type' => 'radios',
      '#title' => t('Arrange multiple values'),
      '#options' => array(
        VIEWS_PIVOT_MODE_MULTI_VALUE_HORICONTAL => t('horicontally'),
        VIEWS_PIVOT_MODE_MULTI_VALUE_VERTICAL => t('vertically'),
      ),
      '#default_value' => $this->options['pivot_mode_multi_values'],
    );

  }

}